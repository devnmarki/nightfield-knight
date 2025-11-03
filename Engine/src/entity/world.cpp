#include "world.hpp"

namespace base
{
	void World::updateEntities()
	{
		for (auto& [type, entity] : _entities)
		{
			for (auto& e : entity)
			{
				e->onUpdate();
			}
		}

		for (auto& [type, widget] : _widgets)
		{
			for (auto& w : widget)
			{
				if (w == nullptr) return;

				w->update();
			}
		}
	}

	void World::renderEntities()
	{
		for (auto& [type, entity] : _entities)
		{
			for (auto& e : entity)
			{
				e->onRender();
			}
		}
	}

	World::EntityMap& World::getEntities()
	{
		return _entities;
	}

	World::WidgetMap& World::getWidgets()
	{
		return _widgets;
	}
}