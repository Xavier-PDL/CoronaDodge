#pragma once
#include <vector>
#include "Entity.h"
#include "LinkedList.h"

class EntityManager
{
	LinkedList<Entity> entities;
public:
	//std::vector<Entity> vEntites;
	void createEntity(EntType entityType);
	void draw(sf::RenderWindow& wnd);
	void update();
};

