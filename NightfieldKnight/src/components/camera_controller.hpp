#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include "engine.hpp"

class CameraController
{
public:
	CameraController() = default;

	void update(base::Entity* target, const glm::vec2& offset = glm::vec2(0.0f), float smooth = 100.0f);
};

#endif