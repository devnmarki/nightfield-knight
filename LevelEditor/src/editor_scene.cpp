#include "editor_scene.hpp"

namespace level_editor
{
	static std::vector<std::shared_ptr<base::Texture>> loadTilesets()
	{
		std::vector<std::shared_ptr<base::Texture>> tilesets;
		nlohmann::json data;
		std::ifstream file("res/data/maps/tilesets.json");

		file >> data;

		for (auto& tileset : data)
		{
			std::string id = tileset["id"].get<std::string>();
			std::string path = tileset["path"].get<std::string>();
			base::AssetManager::loadTexture(id, path);
			tilesets.push_back(base::AssetManager::getTexture(id));
		}

		return tilesets;
	}

	EditorScene::EditorScene()
		: _saveName("map_0.json"), _offgridMouseRect(nullptr)
	{
		
	}

	EditorScene::~EditorScene()
	{
		delete _offgridMouseRect;
	}

	void EditorScene::enter()
	{
		Scene::enter();

		_tilesets = loadTilesets();
		_createTilemap();

		_tileSize = _tilemap->getTileSize();
		_tileSizeScaled = _tileSize * _tilemap->getScale();

		_tilemap->setActiveLayer(_currentLayerIndex);

		_createTileset();
		_initCommands();

		_cameraController = std::make_unique<CameraController>(getCamera());

		_currentLayerText = std::make_unique<base::Font>(
			base::AssetManager::getFont("pixel"),
			"Layer: --",
			glm::u8vec4(255, 255, 255, 255),
			glm::vec2(75.0f, 25.0f)
		);

		_offgridMouseRect = new SDL_Rect{
			.x = _offgridMouseX,
			.y = _offgridMouseY,
			.w = 20,
			.h = 20
		};
	}

	void EditorScene::update()
	{
		Scene::update();

		_handleCommands();
		_updateSelectedTile();
		_handleTilePlacement();

		_updateCurrentLayer();
		_updateCurrentLayerText();

		_updateOffgridMousePos();
		_handleEntityPlacement();

		if (_cameraController != nullptr)
			_cameraController->update();
	}

	void EditorScene::render()
	{
		Scene::render();

		_tilemap->render(&getCamera());
		_renderSelectedTile();

		_currentLayerText->render();

		_renderMapEntities();
	}

	void EditorScene::_handleTileSelection()
	{
		if (!base::Input::isKeyDown(base::Keys::KEY_LSHIFT)) 
			return;

		int scroll = base::Input::getScrollY();
		if (scroll == 0)
			return;

		_selectedTile += (scroll > 0) ? 1 : -1;
		_selectedTile = std::clamp(_selectedTile, 0, _currentTileset->getSpriteCount() - 1);
	}

	void EditorScene::_handleTilesetScrolling()
	{
		if (!base::Input::isKeyDown(base::Keys::KEY_LCTRL))
			return;

		int scroll = base::Input::getScrollY();
		if (scroll == 0)
			return;

		int nextIndex = (scroll > 0)
			? (_currentTilesetIndex + 1) % _tilesets.size()
			: (_currentTilesetIndex - 1 + _tilesets.size()) % _tilesets.size();

		_switchTileset(nextIndex);
	}

	void EditorScene::_updateSelectedTile()
	{
		_handleTilesetScrolling();
		_handleTileSelection();

		glm::vec2 screenMouse(base::Input::getMouseX(), base::Input::getMouseY());
		glm::vec2 worldMouse = getCamera().screenToWorld(screenMouse);
		_mouseX = (std::round(worldMouse.x / _tileSizeScaled) * _tileSizeScaled);
		_mouseY = (std::round(worldMouse.y / _tileSizeScaled) * _tileSizeScaled);
	}

	void EditorScene::_renderSelectedTile()
	{
		if (!_tilemap->getLayers().empty() && _tilemap->getLayers()[_currentLayerIndex].type != MapLayerType::TILE)
			return;

		base::Sprite& selectedTileSprite = _currentTileset->getSprite(_selectedTile);
		selectedTileSprite.alpha = 155;

		base::Renderer::draw(selectedTileSprite, glm::vec2(10.0f), _tilemap->getScale());
		base::Renderer::draw(selectedTileSprite, glm::vec2(_mouseX, _mouseY) - glm::vec2(_tileSizeScaled / 2.0f), _tilemap->getScale(), false, &getCamera());
	}

	void EditorScene::_handleTilePlacement()
	{
		int mx = _mouseX / _tileSizeScaled;
		int my = _mouseY / _tileSizeScaled;

		if (base::Input::isMouseDown(1)) // Place selected tile on left button
		{
			_tilemap->setTile(glm::ivec2(mx, my), _selectedTile, _currentLayerIndex);
			_tilemap->setTilesetIndex(_currentTilesetIndex);
		}
		else if (base::Input::isMouseDown(3)) // Remove hovered tile on right button
		{
			_tilemap->removeTile(glm::ivec2(mx, my), _currentLayerIndex);
		}

		if (base::Input::isMousePressed(2)) // Pickup hovered tile with middle button
		{
			Tile& tile = _tilemap->getTile(glm::ivec2(mx, my), _currentLayerIndex);
			
			if (tile.id != -1)
			{
				_currentTilesetIndex = tile.tilesetId;
				_switchTileset(_currentTilesetIndex);
				_selectedTile = tile.id;
			}
		}
	}

	void EditorScene::_switchTileset(int index)
	{
		if (index < 0 || index >= _tilesets.size())
			return;

		_currentTilesetIndex = index;
		_createTileset();

		_selectedTile = 0;
	}

	void EditorScene::_updateCurrentLayer()
	{
		int prevLayer = _currentLayerIndex;

		if (base::Input::isKeyPressed(base::Keys::KEY_UP))
		{
			_currentLayerIndex = std::min(_currentLayerIndex + 1, static_cast<int>(_tilemap->getLayers().size() - 1));
		}
		else if (base::Input::isKeyPressed(base::Keys::KEY_DOWN))
		{
			_currentLayerIndex = std::max(_currentLayerIndex - 1, 0);
		}

		if (prevLayer != _currentLayerIndex)
		{
			_tilemap->setActiveLayer(_currentLayerIndex);
			prevLayer = _currentLayerIndex;
		}

		static bool showAllLayers = true;
		if (base::Input::isKeyPressed(base::Keys::KEY_O))
		{
			showAllLayers = !showAllLayers;
			_tilemap->setShowOnlyActiveLayer(!showAllLayers);
		}
	}

	void EditorScene::_updateCurrentLayerText()
	{
		static int lastLayerIndex = -1;
		if (lastLayerIndex != _currentLayerIndex)
		{
			if (!_tilemap->getLayers().empty() && _currentLayerIndex < _tilemap->getLayers().size())
				_currentLayerText->setContent("Layer: " + _tilemap->getLayers()[_currentLayerIndex].name);
			else
				_currentLayerText->setContent("Layer: --");

			lastLayerIndex = _currentLayerIndex;
		}
	}
	
	void EditorScene::_createTilemap()
	{
		_tilemap = std::make_unique<Tilemap>(_tilesets, 16, 3.0f);
	}

	void EditorScene::_createTileset()
	{
		_currentTileset = std::make_unique<base::SpriteSheet>(base::SpriteSheetProps{
			.texture = _tilesets[_currentTilesetIndex],
			.grid = glm::ivec2(_tilesets[_currentTilesetIndex]->getWidth() / _tileSize, _tilesets[_currentTilesetIndex]->getHeight() / _tileSize),
			.spriteSize = glm::ivec2(_tileSize)
		});
	}

	void EditorScene::_updateOffgridMousePos()
	{
		_offgridMouseX = base::Input::getMouseX();
		_offgridMouseY = base::Input::getMouseY();

		_offgridMouseRect->x = _offgridMouseX - 10;
		_offgridMouseRect->y = _offgridMouseY - 10;
	}

	void EditorScene::_renderMapEntities()
	{
		for (const auto& layer : _tilemap->getLayers())
		{
			if (layer.type != MapLayerType::ENTITY)
				continue;

			for (const auto& mapEntity : layer.entities)
			{
				glm::vec2 worldPos = getCamera().worldToScreen(mapEntity.position);
				SDL_Rect mapEntityRect = { worldPos.x - 10, worldPos.y - 10, 20, 20 };
				base::Renderer::fillRect(&mapEntityRect, glm::u8vec4(0, 0, 255, 255));
			}
		}

		if (_tilemap->getLayers().empty() || _tilemap->getLayers()[_tilemap->getActiveLayer()].type != MapLayerType::ENTITY)
			return;

		base::Renderer::fillRect(_offgridMouseRect, glm::u8vec4(0, 0, 255, 100));
	}

	void EditorScene::_handleEntityPlacement()
	{
		glm::vec2 worldMouse = getCamera().screenToWorld(glm::vec2(_offgridMouseX, _offgridMouseY));
		
		if (base::Input::isMousePressed(1))
		{
			MapEntity mapEntity = {
				.name = _tilemap->getSelectedEntityName(),
				.position = worldMouse
			};

			_tilemap->addEntity(mapEntity);
		}
		else if (base::Input::isMousePressed(3))
		{
			if (_tilemap->getLayers().empty())
				return;

			MapLayer& currentLayer = _tilemap->getLayers()[_tilemap->getActiveLayer()];
			if (currentLayer.type != MapLayerType::ENTITY)
				return;

			SDL_Rect offgridMouseWorldRect = {
				.x = static_cast<int>(worldMouse.x) - (_offgridMouseRect->w / 2),
				.y = static_cast<int>(worldMouse.y) - (_offgridMouseRect->h / 2),
				.w = _offgridMouseRect->w,
				.h = _offgridMouseRect->h
			};

			auto it = currentLayer.entities.begin();
			while (it != currentLayer.entities.end())
			{
				const auto& mapEntity = *it;

				SDL_Rect mapEntityRect = {
					.x = static_cast<int>(mapEntity.position.x),
					.y = static_cast<int>(mapEntity.position.y),
					.w = 20,
					.h = 20
				};

				if (SDL_HasIntersection(&offgridMouseWorldRect, &mapEntityRect))
				{
					std::cout << "Erasing entity: " << mapEntity.name << std::endl;
					it = currentLayer.entities.erase(it);
					break;
				}
				else
				{
					++it;
				}
			}
		}
	}

	void EditorScene::_initCommands()
	{
		_cmdHandler.addCommand("load", [this](std::istringstream& iss) {
			std::string filename;
			if (iss >> filename)
			{
				if (!_tilemap->load(filename)) return;

				_saveName = filename;
				_currentLayerIndex = 0;
				_tilemap->setActiveLayer(_currentLayerIndex);

				if (!_tilemap->getLayers().empty())
					_currentLayerText->setContent("Layer: " + _tilemap->getLayers()[0].name);
				else
					_currentLayerText->setContent("Layer: --");

				_cameraController->resetCamera();
			}
		});

		_cmdHandler.addCommand("save", [this](std::istringstream& iss) {
			std::string filename;
			if (iss >> filename)
			{
				_saveName = filename;
				_tilemap->save(_saveName);
			}
		});

		_cmdHandler.addCommand("new", [this](std::istringstream& iss) {
			_cameraController->resetCamera();
			_createTilemap();
		});

		_cmdHandler.addCommand("newlayer", [this](std::istringstream& iss) {
			std::string name, type;
			
			if (iss >> name >> type)
			{
				_tilemap->addLayer(MapLayer{
					.name = name,
					.type = stringToLayerType(type),
					.tiles = std::unordered_map<glm::ivec2, Tile> {}
				});
				_currentLayerIndex = _tilemap->getLayers().size() - 1;

				std::cout << "Created new layer '" << name << "'" << std::endl;
			}
			else 
			{
				std::cout << "Usage: newlayer <name> <tile|object|entity>" << std::endl;
			}
		});

		_cmdHandler.addCommand("movelayer", [this](std::istringstream& iss) {
			std::string direction;
			if (iss >> direction)
			{
				if (direction == "up")
				{
					if (_currentLayerIndex < _tilemap->getLayers().size() - 1)
					{
						std::swap(_tilemap->getLayers()[_currentLayerIndex], _tilemap->getLayers()[_currentLayerIndex + 1]);
						_currentLayerIndex++;
					}
				}
				else if (direction == "down")
				{
					if (_currentLayerIndex > 0)
					{
						std::swap(_tilemap->getLayers()[_currentLayerIndex], _tilemap->getLayers()[_currentLayerIndex - 1]);
						_currentLayerIndex--;
					}
				}
			}
		});

		_cmdHandler.addCommand("renamelayer", [this](std::istringstream& iss) {
			std::string oldName, newName;
			if (iss >> oldName >> newName)
			{
				MapLayer* layer = _tilemap->getLayerByName(oldName);
				if (layer != nullptr)
					layer->name = newName;
			}
		});

		_cmdHandler.addCommand("showlayers", [this](std::istringstream& iss) {
			for (size_t i = 0; i < _tilemap->getLayers().size(); i++)
			{
				std::cout << "[" << i << "] " << _tilemap->getLayers()[i].name << std::endl;
			}
		});

		_cmdHandler.addCommand("entity", [this](std::istringstream& iss) {
			std::string name;
			if (iss >> name)
			{
				_tilemap->setSelectedEntityName(name);
			}
		});

		_cmdHandler.addCommand("help", [this](std::istringstream& iss) {
			std::cout << "\nAvailable Commands:\n";
			std::cout << "  load <filename>\n";
			std::cout << "  save <filename>\n";
			std::cout << "  new\n";
			std::cout << "\n";
			std::cout << "  newlayer <name> <tile|object|entity>\n";
			std::cout << "  movelayer <up|down>\n";
			std::cout << "  renamelayer <old_name> <new_name>\n";
			std::cout << "  showlayers\n";
			std::cout << "\n";
			std::cout << "  entity <name>\n";
			std::cout << "\n";
			std::cout << "  help\n";
		});
	}
	
	void EditorScene::_handleCommands()
	{
		if (base::Input::isKeyPressed(base::Keys::KEY_F1))
		{
			system("cls");
			std::cout << "> ";
			std::string command;
			std::getline(std::cin, command);
			_cmdHandler.executeCommands(command);

			std::cout << "\nCommand executed. Press F1 for next command.\n\n";
		}

		if (base::Input::isKeyDown(base::Keys::KEY_LCTRL))
		{
			if (base::Input::isKeyPressed(base::Keys::KEY_S))
			{
				_tilemap->save(_saveName);
			}
		}
	}
}