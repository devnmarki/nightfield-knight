#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include <algorithm>

#include "engine.hpp"

namespace level_editor
{
	class CameraController
	{
	public:
		CameraController(base::Camera& camera);

		void update();
		void resetCamera();
	
	private:
		base::Camera& _camera;

		glm::vec2 _velocity;
		
		inline static constexpr float SPEED = 200.0f;
	};
}

#endif