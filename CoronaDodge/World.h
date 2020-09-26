#pragma once
#include "TextureManager.h"
#include "EntityManager.h"

constexpr int ArenaWidth	= 800;
constexpr int ArenaHeight	= 800;
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
};

