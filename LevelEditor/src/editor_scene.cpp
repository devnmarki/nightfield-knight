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
		: _saveName("map_0.json")
	{
		
	}

	void EditorScene::enter()
	{
		Scene::enter();

		_tilesets = loadTilesets();
		createTilemap();

		_tileSize = _tilemap->getTileSize();
		_tileSizeScaled = _tileSize * _tilemap->getScale();

		createTileset();
		initCommands();

		_cameraController = std::make_unique<CameraController>(getCamera());
	}

	void EditorScene::update()
	{
		Scene::update();

		handleCommands();
		updateSelectedTile();
		handleTilePlacement();

		if (_cameraController != nullptr)
			_cameraController->update();
	}

	void EditorScene::render()
	{
		Scene::render();

		_tilemap->render(&getCamera());
		renderSelectedTile();
	}

	void EditorScene::updateSelectedTile()
	{
		if (base::Input::isKeyDown(base::Keys::KEY_LCTRL))
		{
			if (base::Input::getScrollY() > 0)
			{
				int nextIndex = (_currentTilesetIndex + 1) % _tilesets.size();
				switchTileset(nextIndex);
			}
			else if (base::Input::getScrollY() < 0)
			{
				int prevIndex = (_currentTilesetIndex - 1 + _tilesets.size()) % _tilesets.size();
				switchTileset(prevIndex);
			}
		}
		else if (base::Input::isKeyDown(base::Keys::KEY_LSHIFT))
		{
			if (base::Input::getScrollY() > 0)
			{
				_selectedTile = std::min(_selectedTile + 1, _currentTileset->getSpriteCount() - 1);
			}
			else if (base::Input::getScrollY() < 0)
			{
				_selectedTile = std::max(_selectedTile - 1, 0);
			}
		}

		glm::vec2 screenMouse(base::Input::getMouseX(), base::Input::getMouseY());
		glm::vec2 worldMouse = getCamera().screenToWorld(screenMouse);
		_mouseX = (std::round(worldMouse.x / _tileSizeScaled) * _tileSizeScaled);
		_mouseY = (std::round(worldMouse.y / _tileSizeScaled) * _tileSizeScaled);
	}

	void EditorScene::renderSelectedTile()
	{
		base::Sprite& selectedTileSprite = _currentTileset->getSprite(_selectedTile);
		selectedTileSprite.alpha = 155;

		base::Renderer::draw(selectedTileSprite, glm::vec2(10.0f), _tilemap->getScale());
		base::Renderer::draw(selectedTileSprite, glm::vec2(_mouseX, _mouseY) - glm::vec2(_tileSizeScaled / 2.0f), _tilemap->getScale(), false, &getCamera());
	}

	void EditorScene::handleTilePlacement()
	{
		int mx = _mouseX / _tileSizeScaled;
		int my = _mouseY / _tileSizeScaled;

		if (base::Input::isMouseDown(1)) // Place selected tile on left button
		{
			_tilemap->setTile(glm::ivec2(mx, my), _selectedTile);
			_tilemap->setTilesetIndex(_currentTilesetIndex);
		}
		else if (base::Input::isMouseDown(3)) // Remove hovered tile on right button
		{
			_tilemap->removeTile(glm::ivec2(mx, my));
		}

		if (base::Input::isMousePressed(2)) // Pickup hovered tile with middle button
		{
			Tile& tile = _tilemap->getTile(glm::ivec2(mx, my));
			
			if (tile.id != -1)
			{
				_currentTilesetIndex = tile.tilesetId;
				switchTileset(_currentTilesetIndex);
				_selectedTile = tile.id;
			}
		}
	}

	void EditorScene::switchTileset(int index)
	{
		if (index < 0 || index >= _tilesets.size())
			return;

		_currentTilesetIndex = index;
		createTileset();

		_selectedTile = 0;
	}
	
	void EditorScene::createTilemap()
	{
		_tilemap = std::make_unique<Tilemap>(_tilesets, 16, 3.0f);
	}

	void EditorScene::createTileset()
	{
		_currentTileset = std::make_unique<base::SpriteSheet>(base::SpriteSheetProps{
			.texture = _tilesets[_currentTilesetIndex],
			.grid = glm::ivec2(_tilesets[_currentTilesetIndex]->getWidth() / _tileSize, _tilesets[_currentTilesetIndex]->getHeight() / _tileSize),
			.spriteSize = glm::ivec2(_tileSize)
		});
	}

	void EditorScene::initCommands()
	{
		_cmdHandler.addCommand("load", [this](std::istringstream& iss) {
			std::string filename;
			if (iss >> filename)
			{
				_saveName = filename;
				if (_tilemap->load(filename))
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
			createTilemap();
		});

		_cmdHandler.addCommand("help", [this](std::istringstream& iss) {
			std::cout << "\nAvailable Commands:\n";
			std::cout << "  load <filename>\n";
			std::cout << "  save <filename>\n";
			std::cout << "  new\n";
			std::cout << "  help\n";
		});
	}
	
	void EditorScene::handleCommands()
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