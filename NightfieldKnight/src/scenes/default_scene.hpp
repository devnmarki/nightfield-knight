#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "engine.hpp"

#include "entities/characters/player_entity.hpp"
#include "constants.hpp"

class DefaultScene : public base::Scene
{
public:
	void enter() override;
	void render() override;

private:
	std::shared_ptr<level_editor::Tilemap> _tilemap;
};

#endif