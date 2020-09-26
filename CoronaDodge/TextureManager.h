#pragma once
#include <map>
#include "SFMLBase.h"

using TextureID = uint32_t;

class TextureManager
{
	static TextureManager* pTexMan;
	TextureManager();
public:
	static TextureManager& Get();
	
	~TextureManager();

	void addTexture(TextureID, const char*);
	const sf::Texture& getTexture(TextureID);

private:
	std::map<TextureID, sf::Texture> textMap;
};

