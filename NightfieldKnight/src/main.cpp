#include <iostream>

#include "game.hpp"
#include "constants.hpp"

int main(int argc, char* argv[])
{
	GameSpecifications gameSpecs;
	gameSpecs.windowWidth = 20 * constants::TILE_SIZE_SCALED;
	gameSpecs.windowHeight = 12 * constants::TILE_SIZE_SCALED;
	gameSpecs.title = "Nightfield Knight";

	Game game = Game(gameSpecs);
	game.run();

	return 0;
}