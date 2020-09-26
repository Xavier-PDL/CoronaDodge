#include "TextureManager.h"
#include <map>

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

void TextureManager::addTexture(TextureID id, const char* filePath) {
	if(textMap.find(id) == textMap.end()) {
		textMap[id] = sf::Texture();
		textMap[id].loadFromFile(filePath);
	}
	else {
		throw "ID already assigned a texture";
	}
}

const sf::Texture& TextureManager::getTexture(TextureID id) {
	if (textMap.find(id) == textMap.end()) {
		throw "No texture at this ID";
	}
	else {
		return textMap[id];
	}
}