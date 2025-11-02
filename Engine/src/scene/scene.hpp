#ifndef SCENE_HPP
#define SCENE_HPP

#include "gfx/renderer.hpp"
#include "entity/world.hpp"
#include "scene/camera.hpp"

namespace base
{
	class Scene
	{
	public:
		virtual ~Scene() = default;

		virtual void enter() {}
		virtual void exit() {}

		virtual void update() 
		{
			_world->updateEntities();
		}

		virtual void render() 
		{
			_world->renderEntities();
		}

		std::unique_ptr<World>& getWorld() { return _world; }
		Camera& getCamera() { return _camera; }

	private:
		std::unique_ptr<World> _world = std::make_unique<World>();
		Camera _camera = Camera(glm::vec2(0.0f, 0.0f));
	};
}

#endif