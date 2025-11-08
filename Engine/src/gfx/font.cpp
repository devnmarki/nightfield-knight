#include "font.hpp"

namespace base
{
	Font::Font(TTF_Font* font, const std::string& content, const glm::u8vec4& color, const glm::vec2& position)
		: _content(content)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, _content.c_str(), { color.r, color.g, color.b, color.a });
		_texture = SDL_CreateTextureFromSurface(Window::getInstance().getRenderer(), surface);

		_rect.x = position.x;
		_rect.y = position.y;
		_rect.w = surface->w;
		_rect.h = surface->h;

		SDL_FreeSurface(surface);
	}

	Font::~Font()
	{
		if (_texture)
			SDL_DestroyTexture(_texture);
	}

	void Font::render()
	{
		SDL_RenderCopy(Window::getInstance().getRenderer(), _texture, nullptr, &_rect);
	}
}