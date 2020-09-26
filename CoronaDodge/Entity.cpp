#include "Entity.h"
#include "TextureManager.h"

Entity::Entity()
{
}

Entity::Entity(TextureID texID)
{
	//sf::Vector2f v(.0f, .0f);
	//velocity = v;
	auto texMan = TextureManager::Get();
	setTexture(texMan->getTexture(texID));
	setColor(sf::Color::Green);
}

void Entity::applyTexture(TextureID texID)
{
	auto texMan = TextureManager::Get();
	setTexture(texMan->getTexture(texID));
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}
void Entity::setVelocity(sf::Vector2f v) {
	velocity = v;
}

void Entity::updateTimeToDie(sf::Time* pDT)
{
	timeToDie -= pDT->asSeconds();
}

float Entity::getTimeToDie()
{
	return timeToDie;
}
