#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vec2.hpp>
#include <nlohmann/json.hpp>

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
		const Transform& getTransform() const { return _transform; }

	protected:
		Transform _transform = {};
	};
}

namespace nlohmann
{
	template <>
	struct adl_serializer<glm::vec2>
	{
		static void to_json(json& j, const glm::vec2& vec)
		{
			j = json{
				{"x", vec.x},
				{"y", vec.y}
			};
		}
		static void from_json(const json& j, glm::vec2& vec)
		{
			j.at("x").get_to(vec.x);
			j.at("y").get_to(vec.y);
		}
	};

	template<>
	struct adl_serializer<base::Entity>
	{
		static void to_json(json& j, const base::Entity& entity)
		{
			j = json{
				{ "position", entity.getTransform().position }
			};
		}

		static void from_json(const json& j, base::Entity& entity)
		{
			j.at("position").get_to(entity.getTransform().position);
		}
	};
}

namespace std
{
	template<>
	struct hash<glm::vec2>
	{
		size_t operator()(const glm::vec2& v) const
		{
			return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
		}
	};
}

#endif