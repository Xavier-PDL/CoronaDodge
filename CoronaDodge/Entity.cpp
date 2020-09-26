#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(TextureID texID)
{
	auto texMan = TextureManager::Get();
	setTexture(texMan->getTexture(texID));
	setColor(sf::Color::Green);

}
