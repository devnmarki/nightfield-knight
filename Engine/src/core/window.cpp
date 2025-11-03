#include "window.hpp"

namespace base
{
	static Window* instance = nullptr;

	Window::Window(int width, int height, const std::string& title)
		: _width(width), _height(height), _title(title), _clearColor({ 0, 0, 0, 255 })
	{
		instance = this;
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_handle);

		instance = nullptr;
	}

	void Window::create()
	{
		_handle = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
		if (_handle == nullptr)
		{
			std::cout << "[WINDOW] FATAL: Failed to create window! Message: " << SDL_GetError() << std::endl;
			return;
		}

		_renderer = SDL_CreateRenderer(_handle, -1, SDL_RENDERER_ACCELERATED);
		if (_renderer == nullptr)
		{
			std::cout << "[WINDOW] FATAL: Failed to create renderer! Message: " << SDL_GetError() << std::endl;
		}
	}

	void Window::beginFrame() const
	{
		SDL_SetRenderDrawColor(_renderer, _clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
		SDL_RenderClear(_renderer);
	}

	void Window::endFrame() const
	{
		SDL_RenderPresent(_renderer);
	}

	void Window::clear(const glm::u8vec4& color)
	{
		_clearColor = color;
	}

	void Window::setTitle(const std::string& title)
	{
		_title = title;
		SDL_SetWindowTitle(_handle, _title.c_str());
	}

	int Window::getWidth() const
	{
		return _width;
	}

	int Window::getHeight() const
	{
		return _height;
	}

	std::string Window::getTitle() const
	{
		return _title;
	}

	SDL_Window* Window::getHandle()
	{
		return _handle;
	}

	SDL_Renderer* Window::getRenderer()
	{
		return _renderer;
	}

	Window& Window::getInstance()
	{
		return *instance;
	}
}