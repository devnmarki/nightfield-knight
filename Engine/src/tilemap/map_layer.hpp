#ifndef MAPLAYER_HPP
#define MAPLAYER_HPP

#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

#include "tilemap/tile.hpp" 
#include "entity/entity.hpp"

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

	struct MapEntity
	{
		std::string name;
		glm::vec2 position;
	};

	struct MapLayer
	{
		std::string name = "unnamed";
		MapLayerType type = MapLayerType::TILE;
		std::unordered_map<glm::ivec2, Tile> tiles;
		std::vector<MapEntity> entities = {};
	};
}

namespace nlohmann
{
	template<>
	struct adl_serializer<level_editor::MapEntity>
	{
		static void to_json(json& j, const level_editor::MapEntity& entity)
		{
			j = json{
				{ "name", entity.name },
				{ "position", entity.position }
			};
		}

		static void from_json(const json& j, level_editor::MapEntity& entity)
		{
			j.at("position").get_to(entity.position);
			j.at("name").get_to(entity.name);
		}
	};

	template<>
	struct adl_serializer<level_editor::MapLayer>
	{
		static void to_json(json& j, const level_editor::MapLayer& layer)
		{
			j = json{
				{ "name", layer.name },
				{ "type", level_editor::layerTypeToString(layer.type) }
			};

			if (layer.type == level_editor::MapLayerType::TILE)
			{
				json tilesArray = json::array();
				for (const auto& [pos, tile] : layer.tiles)
				{
					json tileObj;
					tileObj["pos"] = pos;
					tileObj["tile"] = tile;
					tilesArray.push_back(tileObj);
				}
				j["tiles"] = tilesArray;
			}

			if (layer.type == level_editor::MapLayerType::ENTITY)
			{
				json entitiesArray = json::array();
				for (const auto& entity : layer.entities)
				{
					entitiesArray.push_back(entity);
				}
				j["entities"] = entitiesArray;
			}
		}

		static void from_json(const json& j, level_editor::MapLayer& layer)
		{
			layer.name = j.at("name").get<std::string>();
			layer.type = level_editor::stringToLayerType(j.at("type").get<std::string>());

			layer.tiles.clear();
			if (j.contains("tiles"))
			{
				for (const auto& tileObj : j.at("tiles"))
				{
					glm::ivec2 pos = tileObj.at("pos").get<glm::ivec2>();
					level_editor::Tile tile = tileObj.at("tile").get<level_editor::Tile>();
					layer.tiles[pos] = tile;
				}
			}

			layer.entities.clear();
			if (j.contains("entities"))
			{
				for (const auto& entityObj : j.at("entities"))
				{
					level_editor::MapEntity entity = entityObj.get<level_editor::MapEntity>();
					layer.entities.push_back(entity);
				}
			}
		}
	};
}

#endif