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
}