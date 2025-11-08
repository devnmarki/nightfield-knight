#include "engine.hpp"

namespace base
{
	static void _init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			std::cout << "[ENGINE] ERROR: Failed to initialize SDL!" << std::endl;

		if (!(IMG_Init(IMG_INIT_PNG)))
			std::cout << "[ENGINE] ERROR: Failed to initialize SDL_image!" << std::endl;

		if (TTF_Init() == -1)
			std::cout << "[ENGINE] ERROR: Failed to initialize SDL_ttf!" << std::endl;
	}

	Engine::Engine(const EngineSpecifications& specs)
		: _specs(specs), _running(true)
	{
		_init();

		_window = std::make_shared<Window>(_specs.windowWidth, _specs.windowHeight, _specs.windowTitle);
		_window->create();

		Input::init();
	}

	Engine::~Engine()
	{
		base::SceneManager::shutdown();
		base::AssetManager::unload();

		IMG_Quit();
		SDL_Quit();
	}

	void Engine::run()
	{
		SDL_Event e;

		uint64_t currentTime = SDL_GetTicks64();
		
		uint64_t timer = 0;
		uint32_t frames = 0;
		uint32_t fps = 0;

		while (_running)
		{
			Input::update();

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					_running = false;
				}
				if (e.type == SDL_KEYDOWN)
				{
					SDL_Keycode key = e.key.keysym.sym;

					if (key == SDLK_ESCAPE)
						_running = false;
				}
				if (e.type == SDL_MOUSEWHEEL)
				{
					Input::scrollX = e.wheel.x;
					Input::scrollY = e.wheel.y;
				}
			}

			uint64_t now = SDL_GetTicks64();
			Time::deltaTime = (now - currentTime) / 1000.0f;
			currentTime = now;

			SceneManager::updateActiveScene();

			_window->beginFrame();
			SceneManager::renderActiveScene();
			_window->endFrame();

			frames++;
			if (SDL_GetTicks64() - timer >= 1000)
			{
				timer += 1000;
				fps = frames;
				frames = 0;
				_window->setTitle(_specs.windowTitle + " | FPS: " + std::to_string(fps));
			}
		}
	}

	bool Engine::isRunning() const
	{
		return _running;
	}
}