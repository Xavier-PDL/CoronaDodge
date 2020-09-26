#include "World.h"
#include <cstdlib>
#include <ctime>
#include <vector>

World::World()
	:
	arena({ ArenaWidth,ArenaHeight })
{
	arena.setFillColor(sf::Color::White);
	arena.setOutlineColor(sf::Color::Black);
	arena.setOutlineThickness(2.0f);
	auto aSize = arena.getSize();
	arena.setOrigin(aSize.x / 2, aSize.y / 2);
}

void World::init()
{
	srand(time(0));
}

void World::spawnEntity() {
	entities.createEntity(EntType::ET_Enemy);
	sf::Vector2f location(0.f, 0.f);
	
	int quad = rand() % 4;
	switch (quad) {
	case 0:
		location = sf::Vector2f(rand() % (400/2)- 200, rand()% 900);
		break;
	case 1:
		location = sf::Vector2f(rand() % (400/2) +(800 / 2 +800), rand() % 900);
		break;
	case 2:
		location = sf::Vector2f(rand() % 1200, rand() % (300/2) - 300/2);
		break;
	case 3:
		location = sf::Vector2f(rand() % 1200, rand() % (300/2) + (600 +600/2));
	}

	entities.vEntites.back().setPosition(location);
	sf::Vector2f temp(300.f, 300.f); //REPLACE THIS WITH PLAYER LOCATION

	if (1){  //shoot towards player
			sf::Vector2f deltaPos = temp - location;
			deltaPos /= sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
			entities.vEntites.back().putVelocity(deltaPos);
	}
	else {

	}
	// else
		//generate random x,y coord pair within arena
		//sf::Vector2f deltaPos = (x,y) from above - enemy1.getPosition();
		//deltaPos /= sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y))
	
	//.createEntity(EntType::ET_Enemy);
	
	//entities.back().setVelocity(deltaPos);
}

void World::updateEntities() {
	entities.update();
}

void World::draw(sf::RenderWindow& wnd){

	spawnEntity();
	auto wSize = wnd.getSize();
	arena.setPosition(wSize.x / 2, wSize.y / 2);
	wnd.draw(arena);
	entities.draw(wnd);
}
