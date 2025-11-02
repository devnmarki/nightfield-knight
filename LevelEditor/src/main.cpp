#include <iostream>

#include "engine.hpp"
#include "level_editor.hpp"

int main(int argc, char* argv[])
{
	level_editor::LevelEditor editor = level_editor::LevelEditor();
	editor.run();

	return 0;
}