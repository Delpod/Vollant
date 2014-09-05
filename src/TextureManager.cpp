#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = nullptr;

sf::Texture* TextureManager::load(std::string filename, std::string id) {
	sf::Texture *pTexture = new sf::Texture();
	if(!pTexture->loadFromFile(filename))
		return nullptr;
	m_textureMap[id] = pTexture;
	return pTexture;
}