#include "animator.hpp"

namespace base
{
	void Animator::loadAnimations(const std::string& filePath)
	{
		std::ifstream file(filePath);
		json data;

		file >> data;

		std::shared_ptr<SpriteSheet> spriteSheet = AssetManager::getSpriteSheet(data["sprite_sheet_id"]);

		for (auto& [name, animData] : data["animations"].items())
		{
			AnimationProps animationProps = {
				.spriteSheet = spriteSheet,
				.frames = animData["frames"].get<std::vector<int>>(),
				.frameDuration = animData["frame_duration"],
				.loop = animData["loop"],
				.flip = animData["flip"]
			};

			_animations.try_emplace(name, Animation(animationProps));
		}
	}

	void Animator::playAnimation(const std::string& id)
	{
		auto it = _animations.find(id);
		if (it == _animations.end())
		{
			std::cout << "[ANIMATOR] ERROR: Unknown animation '" << id << "'!" << std::endl;
			return;
		}

		if (_currentAnimation != &it->second)
			_currentAnimation = &it->second;
	}

	void Animator::renderCurrentAnimation(const glm::vec2& position, const glm::vec2& scale)
	{
		if (_currentAnimation == nullptr) return;

		_currentAnimation->play();

		Sprite& sprite = _currentAnimation->getCurrentFrameSprite();
		base::Renderer::draw(sprite, position, scale, sprite.flip);
	}

	Animation* Animator::getCurrentAnimation()
	{
		return _currentAnimation;
	}
}