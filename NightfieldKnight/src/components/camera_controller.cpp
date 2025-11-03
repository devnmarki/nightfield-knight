#include "camera_controller.hpp"

void CameraController::update(base::Entity* target, const glm::vec2& offset, float smooth)
{
	glm::vec2 targetPos = target->getTransform().position;
	glm::vec2 screenSize(base::Window::getInstance().getWidth(), base::Window::getInstance().getHeight());
	glm::vec2 desiredPos = targetPos - screenSize / 2.0f + offset;
	glm::vec2 currentPos = base::SceneManager::getActiveScene()->getCamera().getPosition();
	
	float t = 1.0f - std::exp(-smooth * base::Time::deltaTime);
	glm::vec2 smoothedPos = currentPos + (desiredPos - currentPos) * t;

	base::SceneManager::getActiveScene()->getCamera().setPosition(smoothedPos);
}