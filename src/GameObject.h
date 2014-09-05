#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include <SFML/Graphics.hpp>

class GameObject {
public:
	GameObject(sf::Texture& texture, sf::Vector2f position, sf::IntRect textureRect = sf::IntRect(0, 0, 0, 0));
	virtual ~GameObject() {}
	virtual void		update(sf::Time &elapsedTime);
	void				draw(sf::RenderWindow* pWindow);
 	sf::Sprite*			getSprite() { return m_pSprite; }
protected:
	sf::Sprite	 *m_pSprite;
	sf::IntRect  textureRect;
	sf::Vector2f startPos;
};

#endif // GAMEOBJECT_H