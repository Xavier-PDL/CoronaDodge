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
	srand(time(0));
	initPlayer();
}

void World::spawnEntity() {
	entities.createEntity(EntType::ET_Enemy);
	sf::Vector2f location(0.f, 0.f);
	
	float spawnAngle = (float)(rand() % 360);
	float spawnX = cos(spawnAngle);
	float spawnY = sin(spawnAngle);
	location = { spawnX * 1200 + 600, spawnY * 900 + 450 };
	int quad = rand() % 4;

	entities.vEntites.back().setPosition(location);
	sf::Vector2f temp(300.f, 300.f); //REPLACE THIS WITH PLAYER LOCATION

	if (1){  //shoot towards player
			sf::Vector2f deltaPos = temp - location;
			deltaPos /= sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
			entities.vEntites.back().setVelocity(deltaPos);
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

void World::updatePlayerPos(sf::Vector2f deltaPos)
{
//	player.move(deltaPos);
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
	player.setPosition(wSize.x / 2, wSize.y / 2);
}

void World::updateEntities() {
	entities.update();
}

void World::draw(){

	spawnEntity();
	auto wSize = pWnd->getSize();
	arena.setPosition(wSize.x / 2, wSize.y / 2);
	pWnd->draw(arena);
	//pWnd->draw(player);
	player.draw(*pWnd);
	entities.draw(*pWnd);
}

void World::update(sf::Time dt)
{

	auto mousePosI = sf::Mouse::getPosition(*pWnd);
	sf::Vector2f mousePos = { (float)mousePosI.x, (float)mousePosI.y };
	auto wSize = pWnd->getSize();
	sf::Vector2f wCenter = { (float)wSize.x / 2, (float)wSize.y / 2 };
	auto dp = mousePos - wCenter;
	
	auto sprayAngle = (atan2f(dp.y, dp.x) * 180.0f / 3.14f) + 90.0f;
	player.updateSpray(sprayAngle);
	//playerSpray.setRotation(sprayAngle);
}
