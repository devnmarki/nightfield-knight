#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <vector>

#include <vec2.hpp>

#include "gfx/texture.hpp"
#include "gfx/sprite.hpp"

namespace base
{
	struct SpriteSheetProps
	{
		std::shared_ptr<Texture> texture;
		glm::ivec2 grid;
		glm::ivec2 spriteSize;
		bool flip = false;
	};

	class SpriteSheet
	{
	public:
		SpriteSheet(const SpriteSheetProps& props);

		Sprite& getSprite(int index);
		
		const SpriteSheetProps& getProps() const;
		int getSpriteCount() const;

	private:
		SpriteSheetProps _props;
		std::vector<Sprite> _sprites;
	};
}

#endif