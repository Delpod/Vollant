#include "Player.h"

Player::Player(sf::Texture &texture, sf::Vector2f position, sf::IntRect textureRect) :
		GameObject(texture, position, textureRect), state(WALKING), m_birdCounter(0), m_frame(0), m_bFlying(false) {
			m_startingHeight = m_pSprite->getPosition().y;
			m_standingTexture = &texture;
			m_standingRect = textureRect;
			m_clock.restart();
			state = STANDING;
}

void Player::update(sf::Time &elapsedTime) {
	if(state == STANDING && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		state = WALKING;
		m_pSprite->setTexture(*m_walkingTexture);
		m_clock.restart();
	} else if(state == FLYING || state == FALLING || state == FLYINTEHAIR) {
		m_pSprite->setTexture(*m_flyingTexture);
	}
	
	if(state == FLYINTEHAIR) {
		m_bFlying = true;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && state == WALKING) {
		m_pSprite->move(sf::Vector2f(30.0f / elapsedTime.asMilliseconds(), 0.0f));
		if(m_frame >= m_walkingFrames)
			m_frame = 0;
		m_pSprite->setTextureRect(sf::IntRect(m_frame * m_walkingRect.width, 0, m_walkingRect.width, m_walkingRect.height));
		if(m_clock.getElapsedTime().asMilliseconds() > 100.0f) {
			++m_frame;
			m_clock.restart();
		}
	} else if(m_bFlying) {
		if(m_clock.getElapsedTime().asMilliseconds() > 200) {
			m_bFlying = false;
			m_time = m_time.Zero;
			m_clock.restart();
		} else {
			m_pSprite->move(0.0f, (m_clock.getElapsedTime().asMilliseconds( ) - m_time.asMilliseconds()) * -0.1f);
			m_time = sf::milliseconds(m_clock.getElapsedTime().asMilliseconds());
		}
	} else {
		if(state == WALKING)
			setStandingState();
		m_clock.restart();
	}
	
	if(state == FALLING || state == FLYING || state == FLYINTEHAIR) {
		if(!(m_pSprite->getPosition().y >= m_startingHeight)) {
			if(m_clock2.getElapsedTime().asMilliseconds() >= 100.0f) {
				if(m_frame >= m_flyingFrames)
					m_frame = 0;
				m_pSprite->setTextureRect(sf::IntRect(m_frame * m_flyingRect.width, 0, m_flyingRect.width, m_flyingRect.height));
				setOriginCentre();
				++m_frame;
				m_clock2.restart();
				}
		} else {
			m_pSprite->setTexture(*m_standingTexture);
			m_pSprite->setTextureRect(m_standingRect);
			setOriginCentre();
		}
	}
	if(m_pSprite->getPosition().y <= m_startingHeight) {
		if(state == FALLING)
			m_pSprite->move(sf::Vector2f(0.0f, 35.0f / elapsedTime.asMilliseconds()));
		else if(state == FLYING)
			m_pSprite->move(sf::Vector2f(0.0f, 5.0f / elapsedTime.asMilliseconds()));
	}
}

void Player::setWalkingTexture(sf::Texture *texture, sf::IntRect textureRect, unsigned int numFrames) {
	m_walkingTexture = texture;
	m_walkingRect = textureRect;
	m_walkingFrames = numFrames;
}

void Player::setFlyingTexture(sf::Texture *texture, sf::IntRect textureRect, unsigned int numFrames, sf::IntRect collisionRect) {
	m_flyingTexture = texture;
	m_flyingRect = textureRect;
	m_flyingFrames = numFrames;
	m_flyingCollisionRect = collisionRect;
}

sf::IntRect* Player::getCollisionRect() {
	if(state == STANDING)
		return &m_standingRect;
	else if(state == WALKING)
		return &m_walkingRect;
	else if(state == FLYING || state == FALLING || state == FLYINTEHAIR)
		return &m_flyingRect;
		
	return nullptr;
}

void Player::setOriginCentre() {
	m_pSprite->setOrigin(m_pSprite->getLocalBounds().width / 2.0f, m_pSprite->getLocalBounds().height / 2.0f);
}