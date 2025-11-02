#include "input.hpp"

namespace base
{
	void Input::init()
	{
		_currentKeys = SDL_GetKeyboardState(&_keyCount);
		_previousKeys.resize(_keyCount);
	}

	void Input::update()
	{
		for (int i = 0; i < _keyCount; i++)
			_previousKeys[i] = _currentKeys[i];

		SDL_PumpEvents();

		_previousMouseState = _currentMouseState;
		_currentMouseState = SDL_GetMouseState(&_mouseX, &_mouseY);

		scrollX = 0;
		scrollY = 0;

	}

	bool Input::isKeyDown(Keys key)
	{
		return _currentKeys[(int)key];
	}

	bool Input::isKeyPressed(Keys key)
	{
		return _currentKeys[(int)key] && !_previousKeys[(int)key];
	}

	bool Input::isKeyReleased(Keys key)
	{
		return !_currentKeys[(int)key] && _previousKeys[(int)key];
	}

	bool Input::isMouseDown(uint8_t button)
	{
		return (_currentMouseState & SDL_BUTTON(button));
	}

	bool Input::isMousePressed(uint8_t button)
	{
		return (_currentMouseState & SDL_BUTTON(button)) && !(_previousMouseState & SDL_BUTTON(button));
	}

	bool Input::isMouseReleased(uint8_t button)
	{
		return !(_currentMouseState & SDL_BUTTON(button)) && (_previousMouseState & SDL_BUTTON(button));
	}

	int Input::getMouseX() 
	{
		return _mouseX;
	}

	int Input::getMouseY()
	{
		return _mouseY;
	}

	int Input::getScrollX()
	{
		return scrollX;
	}

	int Input::getScrollY()
	{
		return scrollY;
	}
}