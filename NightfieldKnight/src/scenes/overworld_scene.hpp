#ifndef OVERWORLDSCENE_HPP
#define OVERWORLDSCENE_HPP

#include "engine.hpp"

class OverworldScene : public base::Scene
{
public:
	void enter() override;
	void exit() override;
};

#endif