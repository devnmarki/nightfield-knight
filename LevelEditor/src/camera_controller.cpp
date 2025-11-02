#include "camera_controller.hpp"

namespace level_editor
{
	CameraController::CameraController(base::Camera& camera)
		: _camera(camera), _velocity(glm::vec2(0.0f))
	{

	}

	void CameraController::update()
	{
		if (base::Input::isKeyDown(base::Keys::KEY_LCTRL) || base::Input::isKeyDown(base::Keys::KEY_LSHIFT))
			return;

		_velocity = glm::vec2(0.0f);

		if (base::Input::isKeyDown(base::Keys::KEY_A))
			_velocity.x = -1.0f;
		else if (base::Input::isKeyDown(base::Keys::KEY_D))
			_velocity.x = 1.0f;

		if (base::Input::isKeyDown(base::Keys::KEY_W))
			_velocity.y = -1.0f;
		else if (base::Input::isKeyDown(base::Keys::KEY_S))
			_velocity.y = 1.0f;

		int scroll = base::Input::getScrollY();
		if (scroll != 0)
		{
			glm::vec2 mouseScreen(base::Input::getMouseX(), base::Input::getMouseY());
			glm::vec2 prevMouseWorld = _camera.screenToWorld(mouseScreen);

			float oldZoom = _camera.getZoom();
			float newZoom = std::clamp(oldZoom + scroll * 0.1f, 0.5f, 3.0f);
			_camera.setZoom(newZoom);
			
			glm::vec2 nextMouseWorld = _camera.screenToWorld(mouseScreen);
			
			glm::vec2 offset = prevMouseWorld - nextMouseWorld;
			_camera.move(offset);
		}

		_camera.move(_velocity * SPEED * base::Time::deltaTime);
	}

	void CameraController::resetCamera()
	{
		_camera.setPosition(glm::vec2(0.0f));
		_camera.setZoom(1.0f);
	}
}