#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <iostream>
#include <memory>
#include <unordered_map>

#include "scene/scene.hpp"

namespace base
{
	class SceneManager
	{
	public:
		static void addScene(const std::string& sceneId, std::shared_ptr<Scene> scene);
		static void loadScene(const std::string& sceneId);
		
		static void updateActiveScene();
		static void renderActiveScene();

		static void shutdown();

	private:
		inline static std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes = {};
		inline static std::shared_ptr<Scene> _activeScene = nullptr;
	};
}

#endif