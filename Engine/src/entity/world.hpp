#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "entity/entity.hpp"

namespace base
{ 
	class World
	{
	public:
		World() = default;

		template<typename T, typename... Args>
		void createEntity(Args&&... args)
		{
			static_assert(std::is_base_of_v<Entity, T>, "Type must be derived from Entity class");

			auto& list = _entities[typeid(T)];
			auto entity = std::make_unique<T>(std::forward<Args>(args)...);

			entity->onStart();

			list.push_back(std::move(entity));
		}

		void updateEntities();
		void renderEntities();

		using EntityMap = std::unordered_map<std::type_index, std::vector<std::unique_ptr<Entity>>>;

		EntityMap& getEntities();

	private:
		EntityMap _entities;
	};
}

#endif