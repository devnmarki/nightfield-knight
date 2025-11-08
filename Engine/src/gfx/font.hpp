#ifndef FONT_HPP
#define FONT_HPP

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <vec2.hpp>
#include <vec4.hpp>

#include "core/window.hpp"

namespace base
{
	class Font
	{
	public:
		Font(TTF_Font* font, const std::string& content, const glm::u8vec4& color, const glm::vec2& position);
		~Font();

		void render();

	private:
		SDL_Texture* _texture;
		SDL_Rect _rect;
		std::string _content;
	};
}

#endif