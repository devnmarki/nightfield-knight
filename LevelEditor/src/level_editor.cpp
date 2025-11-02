#include "level_editor.hpp"

namespace level_editor
{
	static LevelEditor* _instance = nullptr;

	static void loadAssets()
	{
		//base::AssetManager::loadTexture("overworld_tileset", "res/textures/world/tileset.png");
		//base::AssetManager::loadTexture("fence_tileset", "res/textures/world/fence.png");
	}

	LevelEditor::LevelEditor()
	{
		_instance = this;

		_engine = std::make_shared<base::Engine>(base::EngineSpecifications{
			.windowWidth = 1280,
			.windowHeight = 720,
			.windowTitle = "Level Editor"
		});

		loadAssets();

		base::SceneManager::addScene("editor_scene", std::make_shared<EditorScene>());
		base::SceneManager::loadScene("editor_scene");
	}

	LevelEditor::~LevelEditor()
	{
		_instance = nullptr;
	}
	 
	void LevelEditor::run()
	{
		_engine->run();
	}

	LevelEditor& LevelEditor::getInstance()
	{
		return *_instance;
	}
}