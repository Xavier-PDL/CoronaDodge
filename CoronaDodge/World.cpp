#include "World.h"

World::World()
	:
	arena({800,600})
{
	arena.setFillColor(sf::Color::White);
	arena.setOutlineColor(sf::Color::Black);
	arena.setOutlineThickness(2.0f);
	auto aSize = arena.getSize();
	arena.setOrigin(aSize.x / 2, aSize.y / 2);
}

void World::init()
{
	entities.createEntity(EntType::ET_Enemy);
	entities.createEntity(EntType::ET_Enemy);
}

void World::draw(sf::RenderWindow& wnd)
{
	auto wSize = wnd.getSize();
	arena.setPosition(wSize.x / 2, wSize.y / 2);
	wnd.draw(arena);
	entities.draw(wnd);
}
