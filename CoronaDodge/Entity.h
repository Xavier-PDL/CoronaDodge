#pragma once
#include "SFMLBase.h"
#include "Types.h"

constexpr auto moveSpeed = 150.0f;

class Entity : public sf::Sprite
{
	sf::Vector2f velocity;
	float timeToDie = 5.0f;
public:
	Entity();
	Entity(TextureID texID);
	void applyTexture(TextureID texID);
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f v);
	void updateTimeToDie(sf::Time* pDT);
	float getTimeToDie();
};