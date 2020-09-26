#pragma once
#include "Entity.h"
class Player : public Entity
{
	bool isSpraying;
	sf::ConvexShape playerSpray;
public:
	Player();
	void update(sf::Vector2f deltaPos);
	void checkWall(sf::Vector2f & deltaPos);
	void updateSpray(float sprayAngle);
	void draw(sf::RenderWindow& wnd);
};

