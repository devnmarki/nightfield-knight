#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "engine.hpp"
#include "character.hpp"
#include "constants.hpp"

class PlayerEntity : public Character
{
public:
	PlayerEntity(glm::vec2 position = glm::vec2(0.0f));

	void onStart() override;
	void onUpdate() override;

private:
	void _handleInputs();
	void _updateCurrentAnimation();

private:
	inline static const float MOVEMENT_SPEED = 250.0f;

	std::string _currentState;
};

#endif