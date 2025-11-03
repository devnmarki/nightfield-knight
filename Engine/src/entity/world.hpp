#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "entity/entity.hpp"
#include "ui/widget.hpp"

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

		template<typename T>
		void addWidget(std::shared_ptr<T> widget)
		{
			static_assert(std::is_base_of_v<ui::IWidget, T>, "Type must be derived from IWidget class");
			auto& list = _widgets[typeid(T)];
			list.push_back(widget);
		}

		void updateEntities();
		void renderEntities();

		template<typename T>
		std::vector<T*> query()
		{
			std::vector<T*> result;
			auto it = _entities.find(std::type_index(typeid(T)));

			if (it != _entities.end())
			{
				for (auto& entity : it->second)
				{
					result.push_back(static_cast<T*>(entity.get()));
				}
			}

			return result;
		}

		template<typename T>
		T* queryFirst()
		{
			T* result;
			auto it = _entities.find(std::type_index(typeid(T)));

			if (it != _entities.end())
			{
				result = static_cast<T*>(it->second[0].get());
			}

			return result;
		}

		using EntityMap = std::unordered_map<std::type_index, std::vector<std::unique_ptr<Entity>>>;
		using WidgetMap = std::unordered_map<std::type_index, std::vector<std::shared_ptr<ui::IWidget>>>;

		EntityMap& getEntities();
		WidgetMap& getWidgets();

	private:
		EntityMap _entities;
		WidgetMap _widgets;
	};
}

#endif