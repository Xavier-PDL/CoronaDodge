#include "EntityManager.h"

void EntityManager::createEntity(EntType entityType)
{
	switch (entityType)
	{
	case EntType::ET_Enemy:
		vEntites.push_back(Entity(TexID::Enemy));
		break;
	default:
		break;
	}
}

void EntityManager::draw(sf::RenderWindow& wnd)
{
	for (auto& ent : vEntites)
	{
		wnd.draw(ent);
	}
}
