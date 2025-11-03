#include "game.hpp"

static Game* instance = nullptr;

static void loadAssets()
{
	base::AssetManager::loadSpriteSheets("res/data/sprite_sheets.json");

	base::AssetManager::loadTilemap("map_0", "map_0.json", constants::GAME_SCALE_F);
}

static void loadScenes()
{
	base::SceneManager::addScene("default", std::make_shared<DefaultScene>());
	base::SceneManager::addScene("overworld", std::make_shared<OverworldScene>());
	base::SceneManager::loadScene("default");
}

Game::Game(const GameSpecifications& specs)
	: _specs(specs)
{
	instance = this;

	_engine = std::make_shared<base::Engine>(base::EngineSpecifications{
		.windowWidth = _specs.windowWidth,
		.windowHeight = _specs.windowHeight,
		.windowTitle = _specs.title
	});

	loadAssets();
	loadScenes();
}

Game::~Game()
{
	instance = nullptr;
}

void Game::run()
{
	_engine->run();
}

Game& Game::getInstance()
{
	return *instance;
}