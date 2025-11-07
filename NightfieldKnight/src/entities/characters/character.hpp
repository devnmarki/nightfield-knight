#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <glm.hpp>

#include "engine.hpp"
#include "constants.hpp"

struct CharacterProps
{
	glm::vec2 position = glm::vec2(0.0f);
	float movementSpeed = 0.0f;
	
	std::shared_ptr<base::SpriteSheet> spriteSheet;
	std::string animationsPath = "";
};

class Character : public base::Entity
{
public:
	Character(const CharacterProps& props);

	void onUpdate() override;
	void onRender() override; 

	void handleMovement();
	void updateFacingDirection();

	void setCanMove(bool canMove);

	bool isMoving() const;
	bool canMove() const;

protected:
	CharacterProps _props;

	base::Animator _animator;

	glm::vec2 _velocity = glm::vec2(0.0f); 
	constants::Direction _facingDirection = constants::Direction::DOWN;

private:
	bool _canMove = true;
};

#endif