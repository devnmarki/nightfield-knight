#include "character.hpp"

Character::Character(const CharacterProps& props)
	: _props(props)
{
	_transform.position = _props.position;
	_transform.scale = constants::GAME_SCALE;

	if (!_props.animationsPath.empty())
		_animator.loadAnimations("res/data/animations/" + _props.animationsPath);
}

void Character::onUpdate()
{
	handleMovement();
	updateFacingDirection();
}

void Character::onRender()
{
	if (_animator.getCurrentAnimation() == nullptr)
	{
		base::Renderer::draw(
			_props.spriteSheet->getSprite(0),
			_transform.position,
			_transform.scale,
			false,
			&base::SceneManager::getActiveScene()->getCamera()
		);
	}
	
	_animator.renderCurrentAnimation(
		_transform.position,
		_transform.scale
	);
}

void Character::handleMovement()
{
	if (isMoving())
		_velocity = glm::normalize(_velocity);

	_transform.position.x += _velocity.x * _props.movementSpeed * base::Time::deltaTime;
	_transform.position.y += _velocity.y * _props.movementSpeed * base::Time::deltaTime;
}

void Character::updateFacingDirection()
{
	if (glm::length(_velocity) == 0.0f)
		return;

	if (std::abs(_velocity.x) > std::abs(_velocity.y))
		_facingDirection = _velocity.x > 0 ? constants::Direction::RIGHT : constants::Direction::LEFT;
	else
		_facingDirection = _velocity.y > 0 ? constants::Direction::DOWN : constants::Direction::UP;
}

bool Character::isMoving() const
{
	return _velocity.x != 0.0f || _velocity.y != 0.0f;
}