#include <iostream>

#include "game.hpp"

int main(int argc, char* argv[])
{
	GameSpecifications gameSpecs;
	gameSpecs.windowWidth = 1280;
	gameSpecs.windowHeight = 720;
	gameSpecs.title = "Nightfield Knight";

	Game game = Game(gameSpecs);
	game.run();

	return 0;
}