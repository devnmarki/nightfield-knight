#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vec2.hpp>

namespace base
{
	class Camera
	{
	public:
		Camera(const glm::vec2& position = glm::vec2(0.0f));

		glm::vec2 worldToScreen(const glm::vec2& worldPos) const;
		glm::vec2 screenToWorld(const glm::vec2& screenPos) const;

		void move(const glm::vec2& offset);

		void setPosition(const glm::vec2& position);
		void setZoom(float zoom);

		glm::vec2 getPosition() const;
		float getZoom() const;

	private:
		glm::vec2 _position;
		float _zoom;
	};
}

#endif