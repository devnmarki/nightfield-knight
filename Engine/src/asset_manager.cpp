#include "asset_manager.hpp"

namespace base
{
	void AssetManager::loadTexture(const std::string& id, const std::string& filePath)
	{
		if (_textures.find(id) != _textures.end())
		{
			std::cout << "[ASSET_MANAGER] ERROR: Texture " << id << " already exists." << std::endl;
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

	void AssetManager::unload()
	{
		_spriteSheets.clear();
		_textures.clear();
	}
}