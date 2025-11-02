#include "texture.hpp"

namespace base
{
	Texture::Texture(SDL_Renderer* renderer, const std::string& filePath)
		: _width(0), _height(0), _handle(nullptr)
	{
		_handle = IMG_LoadTexture(renderer, filePath.c_str());
		if (_handle == nullptr)
		{
			std::cout << "[TEXTURE] ERROR: Failed to create texture. Message: " << IMG_GetError() << std::endl;
		}

		SDL_SetTextureBlendMode(_handle, SDL_BLENDMODE_BLEND);
		SDL_QueryTexture(_handle, nullptr, nullptr, &_width, &_height);
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(_handle);
	}

	SDL_Texture* Texture::getHandle()
	{
		return _handle;
	}

	int Texture::getWidth()
	{
		return _width;
	}

	int Texture::getHeight()
	{
		return _height;
	}
}