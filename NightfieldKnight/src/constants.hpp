#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <unordered_map>
#include <string>

#include <vec2.hpp>

namespace constants
{
	inline static constexpr float GAME_SCALE_F = 4.0f;
	inline static const glm::vec2 GAME_SCALE = glm::vec2(GAME_SCALE_F); 

	inline static constexpr int TILE_SIZE = 16;
	inline static constexpr int TILE_SIZE_SCALED = 16 * GAME_SCALE_F;
	
	enum class Direction
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	};

	inline static std::unordered_map<Direction, std::string> DIRECTION_TO_STRING_MAP = {
		{ Direction::UP, "up" },
		{ Direction::DOWN, "down" },
		{ Direction::LEFT, "left" },
		{ Direction::RIGHT, "right" },
	};
}

#endif