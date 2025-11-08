#include "font.hpp"

namespace base
{
	Font::Font(TTF_Font* font, const std::string& content, const glm::u8vec4& color, const glm::vec2& position)
		: _font(font), _content(content), _color(color)
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

	void Font::setContent(const std::string& content)
	{
		if (_content == content)
			return;

		_content = content;
		_regenerate();
	}

	void Font::_regenerate()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
			_texture = nullptr;
		}

		SDL_Color color = { _color.r, _color.g, _color.b, _color.a };
		SDL_Surface* surface = TTF_RenderText_Solid(_font, _content.c_str(), color);

		if (surface)
		{
			_texture = SDL_CreateTextureFromSurface(Window::getInstance().getRenderer(), surface);
			_rect.w = surface->w;
			_rect.h = surface->h;
			SDL_FreeSurface(surface);
		}
	}
}