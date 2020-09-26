#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(TextureID texID)
{
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