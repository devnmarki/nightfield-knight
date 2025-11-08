#ifndef EDITORSCENE_HPP
#define EDITORSCENE_HPP

#include <fstream>

#include <nlohmann/json.hpp>

#include "engine.hpp"
#include "engine_ui.hpp"
#include "command_handler.hpp"
#include "camera_controller.hpp"

namespace level_editor
{
	class EditorScene : public base::Scene
	{
	public:
		EditorScene();

		void enter() override;
		void update() override;
		void render() override;

	private:
		void updateSelectedTile();
		void renderSelectedTile();
		void handleTilePlacement();
		void switchTileset(int index);
		void updateCurrentLayer();

		void createTilemap();
		void createTileset();

		void initCommands();
		void handleCommands();

	private:
		std::unique_ptr<base::SpriteSheet> _currentTileset;
		std::unique_ptr<Tilemap> _tilemap;
		int _selectedTile = 0;
		int _currentLayerIndex = 0;
		int _tileSize = 0;
		int _tileSizeScaled = 0;

		int _currentTilesetIndex = 0;
		std::vector<std::shared_ptr<base::Texture>> _tilesets;

		int _mouseX = 0;
		int _mouseY = 0;

		io::CommandHandler _cmdHandler;
		std::string _saveName;

		std::unique_ptr<CameraController> _cameraController;

		std::unique_ptr<base::Font> _font;
	};
}

#endif