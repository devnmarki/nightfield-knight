#include "asset_manager.hpp"
#include "tilemap/tilemap.hpp"

namespace base
{
	void AssetManager::loadTexture(const std::string& id, const std::string& filePath)
	{
		if (_textures.find(id) != _textures.end())
		{
			std::cout << "[ASSET_MANAGER] WARNING: Texture " << id << " already exists." << std::endl;
			return;
		}

		std::shared_ptr<Texture> target = std::make_shared<Texture>(base::Window::getInstance().getRenderer(), filePath);
		_textures.emplace(id, target);

		std::cout << "[ASSET_MANAGER]: MESSAGE: Loaded texture " << id << " successfully." << std::endl;
	}

	void AssetManager::loadSpriteSheets(const std::string& filePath)
	{
		std::ifstream file(filePath);

		if (!file.is_open())
		{
			std::cout << "[ASSET_MANAGER] ERROR: Could not open sprite sheet file " << filePath << "." << std::endl;
			return;
		}

		json data;
		file >> data;

		for (auto& spriteSheet : data)
		{
			auto& texture = spriteSheet["texture"];
			loadTexture(texture["texture_id"].get<std::string>(), texture["path"].get<std::string>());

			SpriteSheetProps props = {
				.texture = getTexture(texture["texture_id"].get<std::string>()),
				.grid = glm::vec2(spriteSheet["columns"], spriteSheet["rows"]),
				.spriteSize = glm::vec2(spriteSheet["frame_width"], spriteSheet["frame_height"]),
				.flip = spriteSheet["flip"].get<bool>()
			};

			_spriteSheets.emplace(spriteSheet["id"], std::make_shared<SpriteSheet>(props));
		
			std::cout << "[ASSET_MANAGER]: MESSAGE: Loaded sprite sheet " << spriteSheet["id"] << " successfully." << std::endl;
		}
	}

	std::shared_ptr<level_editor::Tilemap> AssetManager::loadTilemap(const std::string& id, const std::string& filePath, float scale)
	{
		auto it = _tilemaps.find(id);
		if (it != _tilemaps.end())
		{
			std::cout << "[ASSET_MANAGER] WARNING: Tilemap '" << "' already exists!" << std::endl;
			return nullptr;
		}

		std::vector<std::shared_ptr<base::Texture>> tilesets;
		nlohmann::json tilesetsData;
		std::ifstream tilesetsFile("res/data/maps/tilesets.json");

		tilesetsFile >> tilesetsData;
		tilesetsFile.close();

		for (auto& tileset : tilesetsData)
		{
			std::string id = tileset["id"].get<std::string>();
			std::string path = tileset["path"].get<std::string>();
			base::AssetManager::loadTexture(id, path);
			tilesets.push_back(base::AssetManager::getTexture(id));
		}

		nlohmann::json tilemapData;
		std::string fullTilemapPath = "res/data/maps/" + filePath;
		std::ifstream tilemapFile(fullTilemapPath.c_str());

		tilemapFile >> tilemapData;
		tilemapFile.close();

		std::shared_ptr<level_editor::Tilemap> tilemap = std::make_shared<level_editor::Tilemap>(tilesets, tilemapData["tile_size"], scale);
		tilemap->load(filePath);
		
		_tilemaps.emplace(id, tilemap);

		std::cout << "[ASSET_MANAGER] MESSAGE: Loaded tilemap '" << id << "' successfully!" << std::endl;

		return tilemap;
	}

	std::shared_ptr<Texture> AssetManager::getTexture(const std::string& id)
	{
		if (_textures.find(id) == _textures.end())
		{
			std::cout << "[ASSET_MANAGER] ERROR: Texture " << id << " does not exist." << std::endl;
			return nullptr;
		}

		return _textures.at(id);
	}

	std::shared_ptr<SpriteSheet> AssetManager::getSpriteSheet(const std::string& id)
	{
		if (_spriteSheets.find(id) == _spriteSheets.end())
		{
			std::cout << "[ASSET_MANAGER] ERROR: Sprite Sheet " << id << " does not exist." << std::endl;
			return nullptr;
		}

		return _spriteSheets.at(id);
	}

	std::shared_ptr<level_editor::Tilemap> AssetManager::getTilemap(const std::string& id)
	{
		if (_tilemaps.find(id) == _tilemaps.end())
		{
			std::cout << "[ASSET_MANAGER] ERROR: Tilemap " << id << " does not exist." << std::endl;
			return nullptr;
		}

		return _tilemaps.at(id);
	}

	void AssetManager::unload()
	{
		_spriteSheets.clear();
		_textures.clear();
	}
}