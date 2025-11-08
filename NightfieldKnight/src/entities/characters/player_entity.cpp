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

	_handleInputs();
	_updateCurrentAnimation();
	_resetActions();

	setCanMove(!_inAction);
}

void PlayerEntity::_handleInputs()
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

	_currentAttackTime += base::Time::deltaTime;
	if (base::Input::isMousePressed(1) && !_inAction && _currentAttackTime >= ATTACK_RATE)
	{
		_attack();
		_currentAttackTime = 0.0f;
	}
}

void PlayerEntity::_attack()
{
	_inAction = true;
	
	// TODO: Attack logic

	std::cout << "Attacking" << std::endl;
}

void PlayerEntity::_resetActions()
{
	if (!_inAction) return;

	if (_currentAttackTime >= ATTACK_RATE)
	{
		_inAction = false;
	}
}

void PlayerEntity::_updateCurrentAnimation()
{
	if (!_inAction)
		_currentState = isMoving() ? "walk" : "idle";
	else
		_currentState = "action";

	std::string animationKey = _currentState + "_" + constants::DIRECTION_TO_STRING_MAP[_facingDirection];
	_animator.playAnimation(animationKey);
}