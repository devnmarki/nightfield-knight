#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "tilemap/tile.hpp"
#include "tilemap/map_layer.hpp"
#include "gfx/renderer.hpp"
#include "asset_manager.hpp"
#include "core/window.hpp"

using json = nlohmann::json;

namespace level_editor
{
	class Tilemap
	{
	public:
		using TexturePtr = std::shared_ptr<base::Texture>;

		Tilemap(std::vector<TexturePtr> tilesets, int tileSize = 16, float scale = 1.0f);

		void setTile(const glm::ivec2& pos, int id, int layerId);
		void removeTile(const glm::ivec2& pos, int layerId);
		Tile& getTile(const glm::ivec2& position, int layerId);
		
		void addLayer(const MapLayer& layer);
		MapLayer* getLayerByName(const std::string& name);

		void render(base::Camera* camera);

		void save(const std::string& filePath);
		bool load(const std::string& filename);

		void setTilesetIndex(int index);
		void setActiveLayer(int index);
		void setShowOnlyActiveLayer(bool show);

		std::vector<MapLayer>& getLayers();
		int getTilesetIndex() const;
		int getActiveLayer() const;
		bool showOnlyActiveLayer() const;
		int getTileSize() const;
		float getScale() const;

	private:
		int _tileSize;
		float _scale;
		std::vector<MapLayer> _layers;
		int _activeLayer;
		bool _showOnlyActiveLayer;

		std::vector<TexturePtr> _tilesets;
		int _tilesetIndex;
	};
}

#endif