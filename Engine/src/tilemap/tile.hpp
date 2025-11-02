#ifndef TILE_HPP
#define TILE_HPP

#include <vec2.hpp>
#include <nlohmann/json.hpp>

#include "gfx/texture.hpp"

namespace level_editor
{
	struct Tile
	{
		glm::ivec2 position;
		int id = -1;
        int tilesetId = 0;
		SDL_Rect srcRect;
	};
}

namespace nlohmann
{
    template <>
    struct adl_serializer<SDL_Rect>
    {
        static void to_json(json& j, const SDL_Rect& rect)
        {
            j = json{
                {"x", rect.x},
                {"y", rect.y},
                {"w", rect.w},
                {"h", rect.h}
            };
        }
        static void from_json(const json& j, SDL_Rect& rect)
        {
            j.at("x").get_to(rect.x);
            j.at("y").get_to(rect.y);
            j.at("w").get_to(rect.w);
            j.at("h").get_to(rect.h);
        }
    };

    template <>
    struct adl_serializer<glm::ivec2>
    {
        static void to_json(json& j, const glm::ivec2& vec)
        {
            j = json{
                {"x", vec.x},
                {"y", vec.y}
            };
        }
        static void from_json(const json& j, glm::ivec2& vec)
        {
            j.at("x").get_to(vec.x);
            j.at("y").get_to(vec.y);
        }
    };

    template <>
    struct adl_serializer<level_editor::Tile>
    {
        static void to_json(json& j, const level_editor::Tile& tile)
        {
            j = json{
                {"position", tile.position},
                {"id", tile.id},
                {"tileset_id", tile.tilesetId},
                {"src_rect", tile.srcRect}
            };
        }
        static void from_json(const json& j, level_editor::Tile& tile)
        {
            j.at("position").get_to(tile.position);
            j.at("id").get_to(tile.id);
            j.at("tileset_id").get_to(tile.tilesetId);
            j.at("src_rect").get_to(tile.srcRect);
        }
    };
}

namespace std
{
    template<>
    struct hash<glm::ivec2>
    {
        size_t operator()(const glm::ivec2& v) const
        {
            return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
        }
    };
}

#endif