#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager{
public:
	static TextureManager* Instance() {
		if(s_pInstance == nullptr)
			s_pInstance = new TextureManager();
		return s_pInstance;
	}
	sf::Texture* load(std::string filename, std::string id);
	sf::Texture* getTexture(std::string id) { return m_textureMap[id]; }
	void clearFromTextureMap(std::string id) { m_textureMap.erase(id); }
	void clearTextureMap() { m_textureMap.clear(); }
private:
	TextureManager() {}
	std::map<std::string, sf::Texture*> m_textureMap;
	static TextureManager* s_pInstance;
};

#endif // TEXTUREMANAGER_H