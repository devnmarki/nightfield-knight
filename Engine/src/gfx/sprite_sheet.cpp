#include "sprite_sheet.hpp"

namespace base
{
	SpriteSheet::SpriteSheet(const SpriteSheetProps& props)
		: _props(props)
	{
		for (int y = 0; y < _props.grid.y; y++)
		{
			for (int x = 0; x < _props.grid.x; x++)
			{
				Sprite sprite = Sprite{
					.texture = _props.texture,
					.source = {
						.x = x * _props.spriteSize.x,
						.y = y * _props.spriteSize.y,
						.w = _props.spriteSize.x,
						.h = _props.spriteSize.y
					},
					.flip = _props.flip
				};

				_sprites.push_back(sprite);
			}
		}
	}

	Sprite& SpriteSheet::getSprite(int index)
	{
		return _sprites[index];
	}

	const SpriteSheetProps& SpriteSheet::getProps() const
	{
		return _props;
	}

	int SpriteSheet::getSpriteCount() const
	{
		return _sprites.size();
	}
}