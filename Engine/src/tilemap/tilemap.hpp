#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "tilemap/tile.hpp"
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

		void setTile(const glm::ivec2& pos, int id);
		void removeTile(const glm::ivec2& pos);
		Tile& getTile(const glm::ivec2& position);

		void render(base::Camera* camera);

		void save(const std::string& filePath);
		bool load(const std::string& filename);

		void setTilesetIndex(int index);

		int getTilesetIndex() const;
		int getTileSize() const;
		float getScale() const;

	private:
		int _tileSize;
		float _scale;
		std::unordered_map<glm::ivec2, Tile> _tiles;

		std::vector<TexturePtr> _tilesets;
		int _tilesetIndex;
	};
}

#endif