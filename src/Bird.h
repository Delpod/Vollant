#ifndef BIRD_H
#define BIRD_H
#include "GameObject.h"
#include <SFML/Audio.hpp>

class Bird : public GameObject {
public:
	Bird(sf::Texture &texture, sf::Vector2f position, sf::IntRect textureRect, std::string text, sf::Font &font, std::string = std::string("data/sounds/iinchadney__wren-in-the-morning"));
	virtual void draw(sf::RenderWindow *pWindow);
	void setString(std::string text);
	std::string getString() { return m_text.getString(); }
	void playSound() { m_sound.play(); }
private:
	sf::Text m_text;
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
};

#endif // BIRD_H