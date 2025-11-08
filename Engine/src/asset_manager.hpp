#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <iostream>
#include <memory>
#include <unordered_map>
#include <fstream>

#include <SDL_ttf.h>
#include <nlohmann/json.hpp>

#include "gfx/texture.hpp"
#include "gfx/sprite_sheet.hpp"
#include "core/window.hpp"

using json = nlohmann::json;

namespace level_editor
{
	class Tilemap;
}

namespace base
{
	class AssetManager
	{
	public:
		static void loadTexture(const std::string& id, const std::string& filePath);
		static void loadSpriteSheets(const std::string& filePath);
		static std::shared_ptr<level_editor::Tilemap> loadTilemap(const std::string& id, const std::string& filePath, float scale = 1.0f);
		static void loadFont(const std::string& id, const std::string& filePath, int size);

		static std::shared_ptr<Texture> getTexture(const std::string& id);
		static std::shared_ptr<SpriteSheet> getSpriteSheet(const std::string& id);
		static std::shared_ptr<level_editor::Tilemap> getTilemap(const std::string& id);
		static TTF_Font* getFont(const std::string& id);

		static void unload();

	private:
		inline static std::unordered_map<std::string, std::shared_ptr<Texture>> _textures = {};
		inline static std::unordered_map<std::string, std::shared_ptr<SpriteSheet>> _spriteSheets = {};
		inline static std::unordered_map<std::string, std::shared_ptr<level_editor::Tilemap>> _tilemaps = {};
		inline static std::unordered_map<std::string, TTF_Font*> _fonts = {};
	};
}

#endif