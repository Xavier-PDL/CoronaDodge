#pragma once
#include <vector>
#include "Entity.h"

class EntityManager
{
	std::vector<Entity> vEntites;
public:
	void createEntity(EntType entityType);
	void draw(sf::RenderWindow& wnd);
};

