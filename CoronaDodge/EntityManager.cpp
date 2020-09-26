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

struct UpdateData
{
	sf::Time* pDT;
	Player& player;
};
void updateCallback(Node<Entity>* pNode, void* pData)
{
	auto pEnt = pNode->pElement;
	UpdateData* pUpdateData = reinterpret_cast<UpdateData*>(pData);
	Player& player = pUpdateData->player;
	pEnt->move(pEnt->getVelocity());
	pEnt->updateTimeToDie(reinterpret_cast<sf::Time*>(pUpdateData->pDT));
	// check for collision with player
	if (pEnt->getGlobalBounds().intersects(pUpdateData->player.getGlobalBounds()))
	{
		player.die();
	}
}

bool removeCallback(Node<Entity>* pNode)
{
	auto pEnt = pNode->pElement;
	if(pEnt->getTimeToDie() <= 0)
		return true;
	return false;
}

void EntityManager::update(sf::Time dt, Player& player)
{
	UpdateData updateData = { &dt, player };
	entities.forEach(updateCallback, &updateData);
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
