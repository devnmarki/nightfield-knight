#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>

#include <SDL.h>

namespace base
{
	enum class Keys
	{
		KEY_UNKNOWN = SDL_SCANCODE_UNKNOWN,

		KEY_A = SDL_SCANCODE_A,
		KEY_B = SDL_SCANCODE_B,
		KEY_C = SDL_SCANCODE_C,
		KEY_D = SDL_SCANCODE_D,
		KEY_E = SDL_SCANCODE_E,
		KEY_F = SDL_SCANCODE_F,
		KEY_G = SDL_SCANCODE_G,
		KEY_H = SDL_SCANCODE_H,
		KEY_I = SDL_SCANCODE_I,
		KEY_J = SDL_SCANCODE_J,
		KEY_K = SDL_SCANCODE_K,
		KEY_L = SDL_SCANCODE_L,
		KEY_M = SDL_SCANCODE_M,
		KEY_N = SDL_SCANCODE_N,
		KEY_O = SDL_SCANCODE_O,
		KEY_P = SDL_SCANCODE_P,
		KEY_Q = SDL_SCANCODE_Q,
		KEY_R = SDL_SCANCODE_R,
		KEY_S = SDL_SCANCODE_S,
		KEY_T = SDL_SCANCODE_T,
		KEY_U = SDL_SCANCODE_U,
		KEY_V = SDL_SCANCODE_V,
		KEY_W = SDL_SCANCODE_W,
		KEY_X = SDL_SCANCODE_X,
		KEY_Y = SDL_SCANCODE_Y,
		KEY_Z = SDL_SCANCODE_Z,

		KEY_0 = SDL_SCANCODE_0,
		KEY_1 = SDL_SCANCODE_1,
		KEY_2 = SDL_SCANCODE_2,
		KEY_3 = SDL_SCANCODE_3,
		KEY_4 = SDL_SCANCODE_4,
		KEY_5 = SDL_SCANCODE_5,
		KEY_6 = SDL_SCANCODE_6,
		KEY_7 = SDL_SCANCODE_7,
		KEY_8 = SDL_SCANCODE_8,
		KEY_9 = SDL_SCANCODE_9,

		KEY_SPACE = SDL_SCANCODE_SPACE,
		KEY_RETURN = SDL_SCANCODE_RETURN,
		KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
		KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
		KEY_TAB = SDL_SCANCODE_TAB,
		KEY_LSHIFT = SDL_SCANCODE_LSHIFT,
		KEY_RSHIFT = SDL_SCANCODE_RSHIFT,
		KEY_LCTRL = SDL_SCANCODE_LCTRL,
		KEY_RCTRL = SDL_SCANCODE_RCTRL,
		KEY_LALT = SDL_SCANCODE_LALT,
		KEY_RALT = SDL_SCANCODE_RALT,

		KEY_F1 = SDL_SCANCODE_F1,
		KEY_F2 = SDL_SCANCODE_F2,
		KEY_F3 = SDL_SCANCODE_F3,
		KEY_F4 = SDL_SCANCODE_F4,
		KEY_F5 = SDL_SCANCODE_F5,
		KEY_F6 = SDL_SCANCODE_F6,
		KEY_F7 = SDL_SCANCODE_F7,
		KEY_F8 = SDL_SCANCODE_F8,
		KEY_F9 = SDL_SCANCODE_F9,
		KEY_F10 = SDL_SCANCODE_F10,
		KEY_F11 = SDL_SCANCODE_F11,
		KEY_F12 = SDL_SCANCODE_F12,

		KEY_UP = SDL_SCANCODE_UP,
		KEY_DOWN = SDL_SCANCODE_DOWN,
		KEY_LEFT = SDL_SCANCODE_LEFT,
		KEY_RIGHT = SDL_SCANCODE_RIGHT,
	};

	class Input
	{
	public:
		static void init();
		static void update();

		static bool isKeyDown(Keys key);
		static bool isKeyPressed(Keys key);
		static bool isKeyReleased(Keys key);

		static bool isMouseDown(uint8_t button);
		static bool isMousePressed(uint8_t button);
		static bool isMouseReleased(uint8_t button);

		static int getMouseX();
		static int getMouseY();

		static int getScrollX();
		static int getScrollY();

	public:
		inline static int scrollX = 0;
		inline static int scrollY = 0;

	private:
		inline static const uint8_t* _currentKeys = nullptr;
		inline static std::vector<uint8_t> _previousKeys;
		inline static int _keyCount = 0;

		inline static uint32_t _currentMouseState = 0;
		inline static uint32_t _previousMouseState = 0;

		inline static int _mouseX = 0;
		inline static int _mouseY = 0;
	};
}

#endif