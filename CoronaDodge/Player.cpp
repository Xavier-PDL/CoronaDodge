#include "Player.h"

Player::Player()
{
	playerSpray.setPointCount(3);
	playerSpray.setPoint(0, { 0, 0 });
	playerSpray.setPoint(1, { -25, -75 });
	playerSpray.setPoint(2, { 25, -75 });
	playerSpray.setFillColor(sf::Color::Cyan);
}

void Player::update(sf::Vector2f deltaPos)
{
	checkWall(deltaPos);
	this->move(deltaPos);
	playerSpray.setPosition(getPosition());	
}

//hardcoded again..
void Player::checkWall(sf::Vector2f &deltaPos) {
	if (this->getPosition().x <= 200 + this->getLocalBounds().width / 2 && deltaPos.x < 0)
		deltaPos.x = 0;
	else if (this->getPosition().x >= 1000 - this->getLocalBounds().width / 2 && deltaPos.x > 0)
		deltaPos.x = 0;
	if (this->getPosition().y <= 150 + this->getLocalBounds().height / 2 && deltaPos.y < 0)
		deltaPos.y = 0;
	else if (this->getPosition().y >= 750 - this->getLocalBounds().height / 2 && deltaPos.y > 0)
		deltaPos.y = 0;
}

void Player::updateSpray(float sprayAngle)
{
	playerSpray.setRotation(sprayAngle);
	isSpraying = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Player::draw(sf::RenderWindow& wnd)
{
	wnd.draw(playerSpray);
	wnd.draw(*this);
}
