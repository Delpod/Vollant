#include "GameObject.h"

GameObject::GameObject(sf::Texture& texture, sf::Vector2f position, sf::IntRect textureRect) {
	sf::IntRect temp;
	if(textureRect == sf::IntRect(0, 0, 0, 0))
		temp = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);
	else
		temp = textureRect;
	m_pSprite = new sf::Sprite(texture, temp);
	m_pSprite->setOrigin(sf::Vector2f(m_pSprite->getLocalBounds().width / 2.0f, m_pSprite->getLocalBounds().height / 2.0f));
	m_pSprite->setPosition(position);
}
void GameObject::update(sf::Time &elapsedTime) {
	
}
void GameObject::draw(sf::RenderWindow* pWindow) {
	pWindow->draw(*m_pSprite);
}
