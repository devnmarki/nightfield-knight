#include "default_scene.hpp"

void DefaultScene::enter()
{
	std::cout << "[DEFAULT_SCENE] Enter!" << std::endl;

	_tilemap = std::make_shared<level_editor::Tilemap>(1, 1, base::AssetManager::getTexture("overworld_tileset"));
	_tilemap->load("map_0.json");

	getWorld()->createEntity<PlayerEntity>(glm::vec2(100.0f, 200.0f));
}

void DefaultScene::render()
{
	_tilemap->render(constants::GAME_SCALE_F);
	Scene::render();
}