#pragma once
#include "TextureManager.h"
#include "EntityManager.h"

constexpr float ArenaWidth	= 800.0f;
constexpr float ArenaHeight	= 600.0f;
class World
{
	// play area
	sf::RectangleShape arena;
	//entity manager
	EntityManager entities;
public:
	World();
	void init();
	void draw(sf::RenderWindow& wnd);
	void updateEntities();
};

