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

void World::setWindow(sf::RenderWindow* pWnd)
{
	this->pWnd = pWnd;
}

void World::init()
{
	srand(unsigned int(time(0)));
	initPlayer();
}

void World::spawnEntity(sf::Time dt) {
	if (spawnVal <= 0) {
		float spawnAngle = (float)(rand() % 360);
		float spawnX = cos(spawnAngle);
		float spawnY = sin(spawnAngle);
		sf::Vector2f entPos = { spawnX * 1200 + 600, spawnY * 900 + 450 };

		sf::Vector2f velocity;
		if (covCount == 0)
		{  //shoot towards player
			velocity = player.getPosition() - entPos;
			covCount++;
		}
		else 
		{
			sf::Vector2f target(rand() % 800 + 200, rand() % 600 + 150);
			velocity = target - entPos;
			covCount++;
			if (covCount == 5)
				covCount = 0;
		}
		velocity /= sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
		entities.createEntity(EntType::ET_Enemy, entPos, velocity * 0.1f);
		spawnVal = (float)((rand() % 15 + 5) / 10.);
	}
	else 
	{
		spawnVal = spawnVal - dt.asSeconds();
	}
}

void World::updatePlayerPos(sf::Vector2f deltaPos)
{
	player.update(deltaPos);
}

void World::initPlayer()
{
	auto texMan = TextureManager::Get();
	player.setTexture(texMan->getTexture(TexID::PlayerNorth));
	player.setColor(sf::Color::Blue);
	auto pRect = player.getLocalBounds();
	player.setOrigin(pRect.width / 2, pRect.height / 2);
	auto wSize = pWnd->getSize();
	player.setPosition(float(wSize.x / 2), float(wSize.y / 2));
}

int bOnce = false;
void World::updateEntities() 
{
	entities.update();
}

void World::draw()
{
	auto wSize = pWnd->getSize();
	arena.setPosition(float(wSize.x / 2), float(wSize.y / 2));
	pWnd->draw(arena);
	player.draw(*pWnd);
	entities.draw(*pWnd);
}

void World::update(sf::Time dt)
{
	spawnEntity(dt);
	auto mousePosI = sf::Mouse::getPosition(*pWnd);
	sf::Vector2f mousePos = { (float)mousePosI.x, (float)mousePosI.y };
	auto wSize = pWnd->getSize();
	sf::Vector2f wCenter = { (float)wSize.x / 2, (float)wSize.y / 2 };
	auto dp = mousePos - wCenter;
	
	auto sprayAngle = (atan2f(dp.y, dp.x) * 180.0f / 3.14f) + 90.0f;
	player.updateSpray(sprayAngle);
}
