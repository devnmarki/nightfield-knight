#include "player_entity.hpp"

using base::Keys;

PlayerEntity::PlayerEntity(glm::vec2 position)
	: Character{
		CharacterProps{
			.position = position,
			.movementSpeed = MOVEMENT_SPEED,

			.spriteSheet = base::AssetManager::getSpriteSheet("player"),
			.animationsPath = "player_animations.json"
		}
	},
	_currentState("idle")
{

}

void PlayerEntity::onStart()
{
	Character::onStart();
}

void PlayerEntity::onUpdate()
{
	Character::onUpdate();

	_currentState = isMoving() ? "walk" : "idle";

	handleInputs();
	updateCurrentAnimation();
}

void PlayerEntity::handleInputs()
{
	_velocity = glm::vec2(0.0f, 0.0f);

	if (base::Input::isKeyDown(Keys::KEY_A))
		_velocity.x = -1.0f;
	else if (base::Input::isKeyDown(Keys::KEY_D))
		_velocity.x = 1.0f;

	if (base::Input::isKeyDown(Keys::KEY_W))
		_velocity.y = -1.0f;
	else if (base::Input::isKeyDown(Keys::KEY_S))
		_velocity.y = 1.0f;
}

void PlayerEntity::updateCurrentAnimation()
{
	std::string animationKey = _currentState + "_" + constants::DIRECTION_TO_STRING_MAP[_facingDirection];
	_animator.playAnimation(animationKey);
}