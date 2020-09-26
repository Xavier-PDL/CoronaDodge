#include "EntityManager.h"

void EntityManager::createEntity(EntType entityType, 
	const sf::Vector2f& pos, const sf::Vector2f& velocity)
{
	switch (entityType)
	{
	case EntType::ET_Enemy:
	{
		auto pEnt = new Entity(TexID::Enemy);
		pEnt->setPosition(pos);
		pEnt->setVelocity(velocity);
		entities.add(pEnt);
		break;
	}
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
}

void drawCallback(Node<Entity>* pNode, void* pWnd)
{
	auto pEnt = pNode->pElement;
	reinterpret_cast<sf::RenderWindow*>(pWnd)->draw(*pEnt);
}

void EntityManager::draw(sf::RenderWindow& wnd)
{
	entities.forEach(drawCallback, &wnd);
}
