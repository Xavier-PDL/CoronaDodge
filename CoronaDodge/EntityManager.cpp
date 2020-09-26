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

void updateCallback(Node<Entity>* pNode, void* pDT)
{
	auto pEnt = pNode->pElement;
	pEnt->move(pEnt->getVelocity());
	pEnt->updateTimeToDie(reinterpret_cast<sf::Time*>(pDT));
}

bool removeCallback(Node<Entity>* pNode)
{
	auto pEnt = pNode->pElement;
	if(pEnt->getTimeToDie() <= 0)
		return true;
	return false;
}

void EntityManager::update(sf::Time dt)
{
	entities.forEach(updateCallback, &dt);
	entities.remove_if(removeCallback);
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
