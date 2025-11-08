#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>

#include "engine.hpp"
#include "scenes/scenes.hpp"

#include <box2d/box2d.h>

struct GameSpecifications
{
	std::string title;
	int windowWidth;
	int windowHeight;
};

class Game
{
public:
	Game(const GameSpecifications& specs);
	~Game();

	void run();

	static Game& getInstance();

private:
	GameSpecifications _specs;

	std::shared_ptr<base::Engine> _engine;
};

#endif