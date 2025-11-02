#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vec2.hpp>

#include "utils/utils.hpp"

namespace base
{
	struct Transform
	{
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 scale = glm::vec2(1.0f);
		float rotation = 0.0f;
	};

	class Entity
	{
	public:
		virtual ~Entity() = default;

		virtual void onStart() {}
		virtual void onUpdate() {}
		virtual void onRender() {}

		Transform& getTransform() { return _transform; }

	protected:
		Transform _transform = {};
	};
}

#endif