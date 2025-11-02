#include "overworld_scene.hpp"

void OverworldScene::enter()
{
	std::cout << "[OVERWORLD_SCENE] Enter!" << std::endl;
}

void OverworldScene::update()
{
	Scene::update();

	if (base::Input::isKeyPressed(base::Keys::KEY_TAB))
		base::SceneManager::loadScene("default");
}

void OverworldScene::exit()
{
	std::cout << "[OVERWORLD_SCENE] Exit!" << std::endl;	
}