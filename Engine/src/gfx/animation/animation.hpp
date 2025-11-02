#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>
#include <vector>

#include "utils/utils.hpp"
#include "gfx/sprite_sheet.hpp"

namespace base
{
	struct AnimationProps
	{
		std::shared_ptr<SpriteSheet> spriteSheet;
		std::vector<int> frames;
		float frameDuration;
		bool loop;
		bool flip;
	};

	class Animation
	{
	public:
		Animation(const AnimationProps& props);

		void play();
		bool finished();

		const AnimationProps& getProps() const;
		int getCurrentFrame() const;
		Sprite& getCurrentFrameSprite() const;

	private:
		AnimationProps _props;

		float _timer;
		int _currentFrameIndex;
	};
}

#endif