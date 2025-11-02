#ifndef LEVELEDITOR_HPP
#define LEVELEDITOR_HPP

#include "engine.hpp"
#include "editor_scene.hpp"

namespace level_editor
{
	class LevelEditor
	{
	public:
		LevelEditor();
		~LevelEditor();

		void run();

		static LevelEditor& getInstance();

	private:
		std::shared_ptr<base::Engine> _engine;
	};
}

#endif