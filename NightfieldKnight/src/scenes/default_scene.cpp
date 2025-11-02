#include "default_scene.hpp"

void DefaultScene::enter()
{
	std::cout << "[DEFAULT_SCENE] Enter!" << std::endl;

	getWorld()->createEntity<PlayerEntity>(glm::vec2(100.0f, 200.0f));
}

void DefaultScene::update()
{
	Scene::update();

	cameraController.update(getWorld()->queryFirst<PlayerEntity>(), glm::vec2(16.0f * constants::GAME_SCALE_F), 15.0f);

	if (base::Input::isKeyPressed(base::Keys::KEY_TAB))
		base::SceneManager::loadScene("overworld");
}

void DefaultScene::render()
{
	base::AssetManager::getTilemap("map_0")->render(&getCamera());

	Scene::render();
}