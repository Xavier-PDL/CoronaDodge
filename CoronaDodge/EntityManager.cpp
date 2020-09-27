#include "EntityManager.h"


Entity* EntityManager::createEntity(EntType entityType, EntityData& entityData)
{
	switch (entityType)
	{
	case EntType::ET_Enemy:
	{
		auto pEnt = new Entity(EntType::ET_Enemy, TexID::Enemy);
		auto bbox = pEnt->getLocalBounds();
		pEnt->setOrigin({ bbox.width / 2, bbox.height / 2 });
		pEnt->setPosition(entityData.entityPos);
		pEnt->setVelocity(entityData.velocity);
		enemies.add(pEnt);
		return pEnt;
		break;
	}
	case EntType::ET_Streak:
	{
		auto pEnt = new Entity(EntType::ET_Streak);
		pEnt->setPosition(entityData.entityPos);
		//pEnt->getStreak()->setPosition(entityData.entityPos);
		pEnt->setTarget(entityData.pEnt);
		streaks.add(pEnt);
		break;
	}
	default:
		break;
	}
	return nullptr;
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
	if (pEnt->getType() == EntType::ET_Enemy)
	{
		Player& player = pUpdateData->player;
		pEnt->move(pEnt->getVelocity());
		pEnt->updateTimeToDie(reinterpret_cast<sf::Time*>(pUpdateData->pDT));
		// check for collision with player
		if (pEnt->getGlobalBounds().intersects(pUpdateData->player.getGlobalBounds()))
		{
			player.die();
		}
	}
	else if (pEnt->getType() == EntType::ET_Streak)
	{
		auto enemyPos = pEnt->getTarget()->getPosition();
		pEnt->adjustStreak(enemyPos);
	}
}

bool removeCallback(Node<Entity>* pNode)
{
	auto pEnt = pNode->pElement;
	if(pEnt->getType() == ET_Enemy && pEnt->getTimeToDie() <= 0)
		return true;
	// spray/streak collition
	return false;
}

void EntityManager::update(sf::Time dt, Player& player)
{
	UpdateData updateData = { &dt, player };
	
	enemies.forEach(updateCallback, &updateData);
	enemies.remove_if(removeCallback);
	streaks.forEach(updateCallback, &updateData);
}

void drawCallback(Node<Entity>* pNode, void* pWnd)
{
	auto pEnt = pNode->pElement;
	if (pEnt->getType() == EntType::ET_Streak)
		reinterpret_cast<sf::RenderWindow*>(pWnd)->draw(pEnt->streakVerts);
	else if (pEnt->getType() == EntType::ET_Enemy)
		reinterpret_cast<sf::RenderWindow*>(pWnd)->draw(*pEnt);
		//reinterpret_cast<sf::RenderWindow*>(pWnd)->draw(*pEnt->getStreak());
}

void EntityManager::draw(sf::RenderWindow& wnd)
{
	streaks.forEach(drawCallback, &wnd);
	enemies.forEach(drawCallback, &wnd);
}
