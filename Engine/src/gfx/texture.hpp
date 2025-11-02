#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

namespace base
{
	class Texture
	{
	public:
		Texture(SDL_Renderer* renderer, const std::string& filePath);
		~Texture();

		SDL_Texture* getHandle();
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* _handle;
		int _width;
		int _height;
	};
}

#endif