#include "EntityManager.h"

void EntityManager::createEntity(EntType entityType)
{
	switch (entityType)
	{
	case EntType::ET_Enemy:
		entities.add(new Entity(TexID::Enemy));
		//vEntites.push_back(Entity(TexID::Enemy));
		break;
	default:
		break;
	}
}

void updateCallback(Node<Entity>* pNode, void*)
{
	auto pEnt = pNode->pElement;
	pEnt->move(pEnt->getVelocity());
}

void EntityManager::update()
{
	entities.forEach(updateCallback);

	//for (auto& ent : vEntites)
	//{
	//	ent.move(ent.getVelocity());
	//}
}

void drawCallback(Node<Entity>* pNode, void* pWnd)
{
	auto pEnt = pNode->pElement;
	reinterpret_cast<sf::RenderWindow*>(pWnd)->draw(*pEnt);
}

void EntityManager::draw(sf::RenderWindow& wnd)
{
	entities.forEach(drawCallback, &wnd);

	//for (auto& ent : vEntites)
	//{
	//	wnd.draw(ent);
	//}
}
