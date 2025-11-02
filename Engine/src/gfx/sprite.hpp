#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>

#include "gfx/texture.hpp"

namespace base
{
	struct Sprite
	{
		std::shared_ptr<Texture> texture;
		SDL_Rect source;
		bool flip = false;
		uint8_t alpha = 255;
	};
}

#endif