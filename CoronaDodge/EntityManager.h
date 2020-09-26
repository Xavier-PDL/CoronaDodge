#pragma once
#include <vector>
#include "Entity.h"

class EntityManager
{
	
public:
	std::vector<Entity> vEntites;
	void createEntity(EntType entityType);
	void draw(sf::RenderWindow& wnd);
	void update();
};

