#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "engine.hpp"

#include "entities/characters/player_entity.hpp"
#include "components/camera_controller.hpp"
#include "constants.hpp"

class DefaultScene : public base::Scene
{
public:
	void enter() override;
	void update() override;
	void render() override;

private:
	CameraController cameraController;
};

#endif