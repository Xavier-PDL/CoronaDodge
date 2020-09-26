#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(TextureID texID)
{
	sf::Vector2f v(.0f, .0f);
	velocity = v;
	auto texMan = TextureManager::Get();
	setTexture(texMan->getTexture(texID));
	setColor(sf::Color::Green);
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}
void Entity::putVelocity(sf::Vector2f v) {
	velocity = v;
}
