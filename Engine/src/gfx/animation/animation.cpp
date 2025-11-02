#include "animation.hpp"

namespace base
{
	Animation::Animation(const AnimationProps& props)
		: _props(props), _timer(0.0f), _currentFrameIndex(0)
	{

	}

	void Animation::play()
	{
		if (_props.frames.empty()) return;
		
		_timer += Time::deltaTime;
		if (_timer >= _props.frameDuration)
		{
			_currentFrameIndex++;
			if (_currentFrameIndex > _props.frames.size() - 1)
				_currentFrameIndex = _props.loop ? 0 : _props.frames.size() - 1;

			_timer -= _props.frameDuration;
		}
	}

	bool Animation::finished()
	{
		return _currentFrameIndex >= _props.frames.size() - 1 && _timer >= _props.frameDuration;
	}

	const AnimationProps& Animation::getProps() const
	{
		return _props;
	}

	int Animation::getCurrentFrame() const
	{
		return _props.frames[_currentFrameIndex];
	}

	Sprite& Animation::getCurrentFrameSprite() const
	{
		Sprite& sprite = _props.spriteSheet->getSprite(getCurrentFrame());
		sprite.flip = _props.flip;

		return sprite;
	}
}