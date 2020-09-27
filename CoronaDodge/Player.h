#pragma once
#include "Entity.h"




class Player : public Entity
{
	bool isSpraying;
	bool alive = true;
	sf::ConvexShape playerSpray;
public:
	Player();
	void reset(sf::RenderWindow* pWnd);
	void update(sf::Vector2f deltaPos);
	void checkWall(sf::Vector2f& deltaPos);
	void checkStreaks(sf::Vector2f& deltaPos);
	void sprayStreaks();
	void updateSpray(float sprayAngle);
	void draw(sf::RenderWindow& wnd);
	void die();
	bool isAlive();
	bool getSprayStatus();
	sf::ConvexShape& getSpray();
};

