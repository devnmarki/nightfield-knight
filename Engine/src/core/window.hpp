#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include <SDL.h>

namespace base
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		void create();

		void beginFrame() const;
		void endFrame() const;

		void setTitle(const std::string& title);

		int getWidth() const;
		int getHeight() const;
		std::string getTitle() const;
		SDL_Window* getHandle();
		SDL_Renderer* getRenderer();

		static Window& getInstance();

	private:
		int _width;
		int _height;
		std::string _title;

		SDL_Window* _handle;
		SDL_Renderer* _renderer;
	};
}

#endif