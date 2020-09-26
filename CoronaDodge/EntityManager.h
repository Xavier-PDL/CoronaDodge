#pragma once
#include <vector>
#include "Entity.h"
#include "LinkedList.h"
#include "Player.h"

class EntityManager
{
	LinkedList<Entity> entities;
public:
	//std::vector<Entity> vEntites;
	void createEntity(EntType entityType, 
		const sf::Vector2f& pos, const sf::Vector2f& velocity);
	void draw(sf::RenderWindow& wnd);
	void update(sf::Time dt, Player& player);
};

