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
	this->move(deltaPos);
	playerSpray.setPosition(getPosition());	
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
