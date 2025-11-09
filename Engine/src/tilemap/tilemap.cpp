#include "tilemap.hpp"

namespace level_editor
{
	Tilemap::Tilemap(std::vector<TexturePtr> tilesets, int tileSize, float scale)
		: 
		_tileSize(tileSize), 
		_tilesets(tilesets), 
		_scale(scale), 
		_tilesetIndex(0), 
		_activeLayer(0), 
		_showOnlyActiveLayer(false)
	{

	}

	Tilemap::~Tilemap()
	{
		_layers.clear();
		_tilesets.clear();
	}

	void Tilemap::setTile(const glm::ivec2& pos, int id, int layerId)
	{
		if (_layers.size() == 0)
		{
			_layers.push_back(MapLayer{
				.name = "tiles_layer",
				.type = MapLayerType::TILE,
				.tiles = std::unordered_map<glm::ivec2, Tile> {}
			});
		}

		int columns = _tilesets[_tilesetIndex]->getWidth() / _tileSize;
		int srcX = (id % columns) * _tileSize;
		int srcY = (id / columns) * _tileSize;

		Tile tile = {
			.position = pos,
			.id = id,
			.tilesetId = _tilesetIndex,
			.layerId = layerId,
			.srcRect = {
				srcX,
				srcY,
				_tileSize,
				_tileSize
			}
		};

		_layers[layerId].tiles[pos] = tile;
	}

	void Tilemap::removeTile(const glm::ivec2& pos, int layerId)
	{
		auto& tiles = _layers[layerId].tiles;
		auto it = tiles.find(pos);
		if (it != tiles.end())
			tiles.erase(pos);
	}

	Tile& Tilemap::getTile(const glm::ivec2& position, int layerId)
	{
		return _layers[layerId].tiles[position];
	}

	void Tilemap::addLayer(const MapLayer& layer)
	{
		_layers.push_back(layer);
	}

	void Tilemap::addEntity(const MapEntity& entity)
	{
		_layers[_activeLayer].entities.push_back(entity);
	}

	MapLayer* Tilemap::getLayerByName(const std::string& name)
	{
		for (MapLayer& layer : _layers)
		{
			if (layer.name == name)
			{
				return &layer;
			}
		}

		std::cout << "Unknown layer '" << name << "'!" << std::endl;

		return nullptr;
	}

	MapEntity* Tilemap::getEntityByName(const std::string& name, int layerIndex)
	{
		for (MapEntity& entity : _layers[layerIndex].entities)
		{
			if (entity.name == name)
			{
				return &entity;
			}
		}

		return nullptr;
	}

	MapEntity* Tilemap::getEntityByPos(const glm::vec2& position, int layerIndex)
	{
		for (MapEntity& entity : _layers[layerIndex].entities)
		{
			if (entity.position == position)
			{
				return &entity;
			}
		}

		return nullptr;
	}

	void Tilemap::render(base::Camera* camera)
	{
		if (_tilesets[_tilesetIndex] == nullptr || camera == nullptr) return;

		int screenWidth = base::Window::getInstance().getWidth();
		int screenHeight = base::Window::getInstance().getHeight();

		glm::vec2 topLeft = camera->screenToWorld(glm::vec2(0, 0));
		glm::vec2 bottomRight = camera->screenToWorld(glm::vec2(screenWidth, screenHeight));

		int minTileX = (int)std::floor(topLeft.x / (_tileSize * _scale));
		int minTileY = (int)std::floor(topLeft.y / (_tileSize * _scale));
		int maxTileX = (int)std::ceil(bottomRight.x / (_tileSize * _scale));
		int maxTileY = (int)std::ceil(bottomRight.y / (_tileSize * _scale));

		for (auto& layer : _layers)
		{
			if (layer.type != MapLayerType::TILE)
				continue;

			for (auto& [tilePos, tile] : layer.tiles)
			{
				if (tilePos.x < minTileX || tilePos.x > maxTileX || 
					tilePos.y < minTileY || tilePos.y > maxTileY)
					continue;

				glm::vec2 position = glm::vec2(tilePos.x * _tileSize * _scale, tilePos.y * _tileSize * _scale);
				
				uint8_t opacity = 255;
				if (_showOnlyActiveLayer && layer.name != _layers[_activeLayer].name && _layers[_activeLayer].type == MapLayerType::TILE)
					opacity = 120;

				base::Renderer::draw(_tilesets[tile.tilesetId], position - glm::vec2((_tileSize * _scale) / 2.0f), &tile.srcRect, glm::vec2(_scale), false, opacity, camera);
			}
		}
	}

	void Tilemap::save(const std::string& filePath)
	{
		json data;
		data["layers"] = _layers;
		data["tile_size"] = _tileSize;

		std::string fullPath = std::string(PROJECT_SOURCE_DIR) + "/res/data/maps/" + filePath;
		std::filesystem::path path(fullPath.c_str());
		std::filesystem::create_directories(path.parent_path());

		std::ofstream file(fullPath.c_str());
		if (!file.is_open())
		{
			std::cerr << "Failed to open file for writing: " << fullPath << std::endl;
			return;
		}

		file << data.dump(4);
		file.flush();
		file.close();

		std::cout << "Saved tilemap successfully at '" << path << "'!" << std::endl;
	}

	bool Tilemap::load(const std::string& filename)
	{
		json data;

		std::string fullPath = std::string(PROJECT_SOURCE_DIR) + "/res/data/maps/" + filename;
		std::ifstream file(fullPath.c_str());

		if (!file.is_open())
		{
			std::cerr << "Failed to open file for reading: " << fullPath << std::endl;
			return false;
		}

		file >> data;

		_layers.clear();
		_layers = data["layers"].get<std::vector<MapLayer>>();

		std::cout << "Loaded tilemap successfully from '" << fullPath << "'!" << std::endl;

		return true;
	}

	void Tilemap::setTilesetIndex(int index)
	{
		_tilesetIndex = index;
	}

	void Tilemap::setActiveLayer(int index)
	{
		_activeLayer = index;
	}

	void Tilemap::setShowOnlyActiveLayer(bool show)
	{
		_showOnlyActiveLayer = show;
	}

	void Tilemap::setSelectedEntityName(const std::string& name)
	{
		_selectedEntityName = name;
	}

	std::vector<MapLayer>& Tilemap::getLayers()
	{
		return _layers;
	}

	int Tilemap::getTilesetIndex() const
	{
		return _tilesetIndex;
	}

	int Tilemap::getActiveLayer() const 
	{
		return _activeLayer;
	}

	bool Tilemap::showOnlyActiveLayer() const
	{
		return _showOnlyActiveLayer;
	}

	int Tilemap::getTileSize() const
	{
		return _tileSize;
	}

	float Tilemap::getScale() const
	{
		return _scale;
	}
	std::string Tilemap::getSelectedEntityName() const
	{
		return _selectedEntityName;
	}
}