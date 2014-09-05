#include "Bird.h"
#include "Game.h"

Bird::Bird(sf::Texture &texture, sf::Vector2f position, sf::IntRect textureRect, std::string textString, sf::Font &font, std::string soundFile) :
	GameObject(texture, position, textureRect), m_text(textString, font, 20) {
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setScale(0.5f, 0.5f);
	m_text.setColor(sf::Color(240, 240, 255));
	m_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	m_text.setPosition(position.x + m_text.getOrigin().x * 0.7f, 180.0f);
	m_buffer.loadFromFile(soundFile);
	m_sound.setBuffer(m_buffer);
}

void Bird::draw(sf::RenderWindow *pWindow) {
	pWindow->draw(*m_pSprite);
	if(Game::Instance()->getPlayer()->state == Game::Instance()->getPlayer()->TALKING && (*Game::Instance()->getBirds())[Game::Instance()->getPlayer()->getBirdCount()] == this) {
		m_text.setColor(sf::Color(0,0,0));
		m_text.move(0.0f, 1.0f);
		pWindow->draw(m_text);
		m_text.move(0.0f, -2.0f);
		pWindow->draw(m_text);
		m_text.move(1.0f, 1.0f);
		pWindow->draw(m_text);
		m_text.move(-2.0f, 0.0f);
		pWindow->draw(m_text);
		m_text.setColor(sf::Color(255,255,255));
		m_text.move(1.0f, 0.0f);
		pWindow->draw(m_text);
	}
}

void Bird::setString(std::string text) {
	m_text.setString(text);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	m_text.setPosition(m_pSprite->getPosition().x + m_text.getOrigin().x - m_pSprite->getOrigin().x, m_pSprite->getPosition().y - m_pSprite->getOrigin().y);
}