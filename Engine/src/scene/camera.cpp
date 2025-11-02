#include "camera.hpp"

namespace base
{
	Camera::Camera(const glm::vec2& position)
		: _position(position), _zoom(1.0f)
	{

	}

	glm::vec2 Camera::worldToScreen(const glm::vec2& worldPos) const
	{
		return (worldPos - _position) * _zoom;
	}

	glm::vec2 Camera::screenToWorld(const glm::vec2& screenPos) const
	{
		return (screenPos / _zoom) + _position;
	}

	void Camera::move(const glm::vec2& offset)
	{
		_position += offset;
	}

	void Camera::setPosition(const glm::vec2& position)
	{
		_position = position;
	}

	void Camera::setZoom(float zoom)
	{
		_zoom = zoom;
	}

	glm::vec2 Camera::getPosition() const
	{
		return _position;
	}

	float Camera::getZoom() const
	{
		return _zoom;
	}
}