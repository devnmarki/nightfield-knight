#ifndef ENGINE_HPP
#define ENGINE_HPP

//------------------------------
// Core
//------------------------------
#include "core/window.hpp"
#include "core/input.hpp"
#include "asset_manager.hpp"
#include "scene/scene_manager.hpp"
#include "entity/entity.hpp"
#include "scene/camera.hpp"
#include "tilemap/tilemap.hpp"

//------------------------------
// GFX
//------------------------------
#include "gfx/renderer.hpp"
#include "gfx/sprite_sheet.hpp"
#include "gfx/animation/animator.hpp"

//------------------------------
// Utils
//------------------------------
#include "utils/utils.hpp" 

namespace base
{
	struct EngineSpecifications
	{
		int windowWidth;
		int windowHeight;
		std::string windowTitle;
	};

	class Engine
	{
	public:
		Engine(const EngineSpecifications& specs);
		~Engine();

		void run();

		bool isRunning() const;

	private:
		EngineSpecifications _specs;
		bool _running;
		std::shared_ptr<Window> _window;
	};
}

#endif