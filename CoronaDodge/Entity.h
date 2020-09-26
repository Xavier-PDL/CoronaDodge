#pragma once
#include "SFMLBase.h"
#include "Types.h"

constexpr auto moveSpeed = 150.0f;

class Entity : public sf::Sprite
{
	sf::Vector2f velocty;
public:
	Entity(TextureID texID);
};

