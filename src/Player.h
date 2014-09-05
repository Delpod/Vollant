#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"

class Player : public GameObject {
public:
	Player(sf::Texture& texture, sf::Vector2f position, sf::IntRect textureRect = sf::IntRect(0, 0, 0, 0));
	virtual void		update(sf::Time &elapsedTime);
	unsigned int		getBirdCount() { return m_birdCounter; }
	void				incrementBirdCount() { ++m_birdCounter; }
	float				getStartingHeight() { return m_startingHeight; }
	void				fly() { m_bFlying = true; m_clock.restart(); m_clock2.restart(); }
	sf::IntRect*		getCollisionRect();
	void				setStandingState() {
							m_pSprite->setTexture(*m_standingTexture);
							m_pSprite->setTextureRect(m_standingRect);
							setOriginCentre();
							state = STANDING;
						}
	void				setWalkingTexture(sf::Texture *texture, sf::IntRect textureRect, unsigned int numFrames);
	void				setFlyingTexture(sf::Texture *texture, sf::IntRect textureRect, unsigned int numFrames, sf::IntRect collisionRect);
	void				setOriginCentre(); 
	enum { STANDING, WALKING, TALKING, FLYING, FALLING, FLYINTEHAIR } state;
private:
	sf::Texture* m_standingTexture;
	sf::Texture* m_walkingTexture;
	sf::Texture* m_flyingTexture;
	sf::IntRect m_standingRect;
	sf::IntRect m_walkingRect;
	sf::IntRect m_flyingRect;
	sf::IntRect m_flyingCollisionRect;
	sf::Clock m_clock;
	sf::Clock m_clock2;
	sf::Time m_time;
	unsigned int m_birdCounter;
	unsigned int m_walkingFrames;
	unsigned int m_flyingFrames;
	unsigned int m_frame;
	float m_startingHeight;
	bool m_bFlying;
};

#endif // PLAYER_H