#ifndef MAPLAYER_HPP
#define MAPLAYER_HPP
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "tilemap/tile.hpp"  // This already includes glm::ivec2 hash and serialization

namespace level_editor
{
	enum class MapLayerType
	{
		TILE = 0,
		ENTITY,
		OBJECT
	};

	inline std::string layerTypeToString(MapLayerType type)
	{
		switch (type)
		{
		case MapLayerType::TILE:
			return "tile";
		case MapLayerType::ENTITY:
			return "entity";
		case MapLayerType::OBJECT:
			return "object";
		default:
			return "tile";
		}
	}

	inline MapLayerType stringToLayerType(const std::string& type)
	{
		if (type == "tile")
			return MapLayerType::TILE;
		else if (type == "entity")
			return MapLayerType::ENTITY;
		else if (type == "object")
			return MapLayerType::OBJECT;
		else
			return MapLayerType::TILE;
	}

	struct MapLayer
	{
		std::string name = "unnamed";
		MapLayerType type = MapLayerType::TILE;
		std::unordered_map<glm::ivec2, Tile> tiles;
	};
}

namespace nlohmann
{
	template<>
	struct adl_serializer<level_editor::MapLayer>
	{
		static void to_json(json& j, const level_editor::MapLayer& layer)
		{
			// Convert unordered_map to array of objects for better JSON structure
			json tilesArray = json::array();
			for (const auto& [pos, tile] : layer.tiles)
			{
				json tileObj;
				tileObj["pos"] = pos;
				tileObj["tile"] = tile;
				tilesArray.push_back(tileObj);
			}

			j = json{
				{ "name", layer.name },
				{ "type", level_editor::layerTypeToString(layer.type) },
				{ "tiles", tilesArray }
			};
		}

		static void from_json(const json& j, level_editor::MapLayer& layer)
		{
			layer.name = j.at("name").get<std::string>();
			layer.type = level_editor::stringToLayerType(j.at("type").get<std::string>());

			layer.tiles.clear();
			for (const auto& tileObj : j.at("tiles"))
			{
				glm::ivec2 pos = tileObj.at("pos").get<glm::ivec2>();
				level_editor::Tile tile = tileObj.at("tile").get<level_editor::Tile>();
				layer.tiles[pos] = tile;
			}
		}
	};
}

#endif