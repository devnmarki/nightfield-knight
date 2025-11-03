#include "scene_manager.hpp"

namespace base
{
	void SceneManager::addScene(const std::string& sceneId, std::shared_ptr<Scene> scene)
	{
		if (_scenes.find(sceneId) != _scenes.end())
		{
			std::cout << "[SCENE_MANAGER] WARNING: Scene '" << sceneId << "' already exists!" << std::endl;
			return;
		}

		_scenes.emplace(sceneId, scene);
	}

	void SceneManager::loadScene(const std::string& sceneId)
	{
		auto it = _scenes.find(sceneId);
		if (it == _scenes.end())
		{
			std::cout << "[SCENE_MANAGER] ERROR: Unknown scene '" << sceneId << "'!";
			return;
		}

		std::shared_ptr<Scene> nextScene = it->second;
		
		if (_activeScene != nextScene)
		{
			if (_activeScene != nullptr)
			{
				_activeScene->exit();
				_activeScene->getWorld()->getEntities().clear();
			}

			_activeScene = nextScene;
			_activeScene->enter();
		}
	}

	void SceneManager::updateActiveScene()
	{
		if (_activeScene == nullptr) return;

		_activeScene->update();
	}

	void SceneManager::renderActiveScene()
	{
		if (_activeScene == nullptr) return;

		_activeScene->render();

		for (auto& [_, widgetList] : _activeScene->getWorld()->getWidgets())
		{
			for (auto& widget : widgetList)
			{
				if (widget == nullptr) return;

				widget->render();
			}
		}
	}

	std::shared_ptr<Scene> SceneManager::getActiveScene()
	{
		return _activeScene;
	}

	void SceneManager::shutdown()
	{
		_activeScene = nullptr;
		_scenes.clear();
	}
}