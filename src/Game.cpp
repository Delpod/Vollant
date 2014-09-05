#include "Game.h"
#include <cmath>
#include "TextureManager.h"

Game* Game::s_pInstance = nullptr;

void Game::init(sf::VideoMode vm, std::string windowName, Uint32 style) {
	m_pWindow = new sf::RenderWindow(vm, windowName, style);
	m_pWindow->setView(sf::View(sf::FloatRect(0, 0, vm.width * 0.5f, vm.height * 0.5f)));
	m_pWindow->setVerticalSyncEnabled(true);
	m_pWindow->setKeyRepeatEnabled(false);
	sf::Image icon = TextureManager::Instance()->load("data/gfx/lark.png", "lark")->copyToImage();
	m_pWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	m_white.setSize(sf::Vector2f(vm.width * 0.5f, vm.height * 0.5f));
	m_white.setOrigin(sf::Vector2f(m_white.getSize().x / 2.0f, m_white.getSize().y / 2.0f));
	m_textFont.loadFromFile("data/fonts/Greenscr.ttf");
	m_music.openFromFile("data/music/klankbeeld-forest-meadow-land-spring.ogg");
	m_music.setLoop(true);
	m_bRunning = true;
	m_bChangeState = true;
	m_stateToDo = (unsigned int)DARKASTRONAUT;
	m_way = 2;
	m_whiteColor = sf::Color(0, 0, 0);
	initDarkAstronaut();
	m_clock2.restart();
	m_clock.restart();
}

void Game::handleEvents() {
	sf::Event event;
	while(m_pWindow->pollEvent(event)) {
		if(state == GAME) {
			if(!m_flyPos.empty()) {
				if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
					if(pPlayer->state != pPlayer->FLYINTEHAIR) {
						if(distance(pPlayer->getSprite()->getPosition(), sf::Vector2f(m_flyPos.front(), pPlayer->getSprite()->getPosition().y)) < 60.0f) {
							if(pPlayer->state == pPlayer->STANDING) {
								pPlayer->state = pPlayer->FLYING;
								m_prevPos = m_flyPos.front();
								++m_flyCount;
								if(m_flyCount != pPlayer->getBirdCount())
									pPlayer->incrementBirdCount();
							} else if(pPlayer->state == pPlayer->FLYING) {
								if(pPlayer->getSprite()->getPosition().y < m_heights.front()) {
									if(bird_state == NORMAL) {
										pPlayer->state = pPlayer->FALLING;
									} else {
										pPlayer->state = pPlayer->FLYINTEHAIR;
										m_clock2.restart();
									}
								} else {
									pPlayer->getSprite()->setPosition(pPlayer->getSprite()->getPosition().x, pPlayer->getSprite()->getPosition().y - 8.5f);
								}
								
							} else if(pPlayer->state == pPlayer->FALLING) {
								if(pPlayer->getSprite()->getPosition().y >= pPlayer->getStartingHeight()) {
									pPlayer->getSprite()->setPosition(pPlayer->getSprite()->getPosition().x, pPlayer->getStartingHeight());
									m_flyPos.pop_front();
									m_heights.pop_front();
									pPlayer->setStandingState();
								}
							}
						} else if(bird_state == NORMAL && distance(pPlayer->getSprite()->getPosition(),
						  m_birds[pPlayer->getBirdCount()]->getSprite()->getPosition()) <
						  m_birds[pPlayer->getBirdCount()]->getSprite()->getLocalBounds().width) {
							if(pPlayer->state == pPlayer->STANDING) {
								pPlayer->state = pPlayer->TALKING;
								m_birds[pPlayer->getBirdCount()]->playSound();
							} else if(pPlayer->state == pPlayer->TALKING) {
								pPlayer->state = pPlayer->STANDING;
								pPlayer->incrementBirdCount();
								if(pPlayer->getBirdCount() >= m_birds.size())
									bird_state = ENDFLY;
							}
						}
					}
				}
			}
		} else if(state == MAINMENU) {
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !m_bChangeState) {
				m_bChangeState = true;
				m_stateToDo = (unsigned int)GAME;
				m_way = 1;
				m_whiteColor = sf::Color(255, 255, 255);
				m_clock2.restart();
			}
		} else if(state == EXIT) {
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !m_bChangeState) {
				m_bChangeState = true;
				m_stateToDo = (unsigned int)DEFEXIT;
				m_way = 1;
				m_whiteColor = sf::Color(255, 255, 255);
				m_clock2.restart();
			}
		}
		
		if(event.type == sf::Event::Closed)
			m_bRunning = false;
	}
}

void Game::update() {
	m_time = sf::milliseconds(m_clock.restart().asMilliseconds());
	if(m_bChangeState) {
		int a;
		if(m_way == 1)
			a = m_clock2.getElapsedTime().asSeconds() * 255;
		else
			a = 255 - m_clock2.getElapsedTime().asSeconds() * 255;
		a = a > 255 ? 255 : (a < 0 ? 0 : a);
		m_white.setFillColor(sf::Color(m_whiteColor.r, m_whiteColor.g, m_whiteColor.b, a));
		if(m_way == 1 && a == 255) {
			switch(m_stateToDo) {
			case (unsigned int)MAINMENU:
				initMainMenu();
				break;
			case (unsigned int)GAME:
				initGame();
				break;
			case (unsigned int)EXIT:
				initExit();
				break;
			case (unsigned int)DEFEXIT:
				m_bRunning = false;
				break;
			default:
				break;
			}
			m_way = 2;
			m_clock2.restart();
		}
		if(m_way == 2 && a == 0)
			m_bChangeState = false;
	}
	
	if(state == GAME) {
		pPlayer->update(m_time);
		if(pPlayer->getSprite()->getPosition().x > m_flyPos.front() && !(distance(pPlayer->getSprite()->getPosition(), sf::Vector2f(m_flyPos.front(), pPlayer->getSprite()->getPosition().y)) < 60.0f)) {
			m_add -= -m_prevPos + m_flyPos.front() + 60.0f;
			m_prevPos = m_flyPos.front();
			m_flyPos.pop_front();
			m_flyPos.push_back(m_flyPos.back() + 450.0f);
			pPlayer->incrementBirdCount();
			++m_flyCount;
			m_birds.push_back(new Bird(*TextureManager::Instance()->load(m_birdsFilenames.front(), m_birdsID.front()),
					sf::Vector2f((float)(m_flyPos.back() - 100), pPlayer->getSprite()->getPosition().y + pPlayer->getSprite()->getOrigin().y - TextureManager::Instance()->getTexture(m_birdsID.front())->getSize().y / 2.0f),
					sf::IntRect(0, 0, 0, 0),
					m_birdTexts.front(),
					m_textFont,
					m_birdsSounds.front()));
			m_birdsID.push_back(m_birdsID.front());
			m_birdsID.pop_front();
			m_birdsFilenames.push_back(m_birdsFilenames.front());
			m_birdsFilenames.pop_front();
			m_birdsSounds.push_back(m_birdsSounds.front());
			m_birdsSounds.pop_front();
			
			for(unsigned int i = m_birds.size() - 1; i >= pPlayer->getBirdCount() ; --i) {
				m_birds[i]->setString(m_birds[i-1]->getString());
			}
		} 
		float mult = (((float)m_flyPos.back() - m_add) / ((float)m_flyPos.back() - m_add + 350.0f));
		if(pPlayer->state != pPlayer->FLYINTEHAIR)
			m_pWindow->setView(sf::View(sf::FloatRect((pPlayer->getSprite()->getPosition().x - m_add) * mult + m_add * mult - 20.0f,
							(pPlayer->getSprite()->getPosition().y - pPlayer->getStartingHeight()) / pPlayer->getStartingHeight() * 30.0f + 30.0f,
							m_pWindow->getDefaultView().getSize().x * 0.5f,
							m_pWindow->getDefaultView().getSize().y * 0.5f)));
		else m_pWindow->setView(sf::View(sf::FloatRect((pPlayer->getSprite()->getPosition().x - m_add) * mult + m_add * mult - 20.0f,
							(pPlayer->getSprite()->getPosition().y - pPlayer->getStartingHeight()) / pPlayer->getStartingHeight() * 165.0f + 145.3f,
							m_pWindow->getDefaultView().getSize().x * 0.5f,
							m_pWindow->getDefaultView().getSize().y * 0.5f)));
		
		if(m_pWindow->getView().getCenter().x - m_pWindow->getView().getSize().x / 2.0f >= m_background.getPosition().x + m_background.getLocalBounds().width) {
			m_background.setPosition(m_background2.getPosition());
			m_background2.setPosition(m_background.getPosition().x + m_background.getLocalBounds().width, 0.0f);
		}
		m_flyText.setPosition(m_pWindow->getView().getCenter().x, 50.0f);
	m_talkText.setPosition(m_pWindow->getView().getCenter().x, 50.0f);
		if(pPlayer->state == pPlayer->FLYINTEHAIR && m_clock2.getElapsedTime().asSeconds() > 5.0f && !m_bChangeState) {
			m_bChangeState = true;
			m_stateToDo = (unsigned int)EXIT;
			m_way = 1;
			m_whiteColor = sf::Color(255, 255, 255);
			m_clock2.restart();
		}
	} else if(!m_bChangeState &&state == DARKASTRONAUT) {
		if(m_clock2.getElapsedTime().asSeconds() > 2.0f) {
			m_bChangeState = true;
			m_stateToDo = (unsigned int)MAINMENU;
			m_way = 1;
			m_whiteColor = sf::Color(255, 255, 255);
			m_clock2.restart();
		}
	}
	m_white.setPosition(m_pWindow->getView().getCenter());
}

void Game::draw() {
	if(state == DARKASTRONAUT)
		m_pWindow->clear(sf::Color(0, 0, 0));
	else if(state != GAME)
		m_pWindow->clear(sf::Color(245, 245, 255));
	else
		m_pWindow->clear(sf::Color(147, 210, 255));
	
	if(state == GAME) {
		m_pWindow->draw(m_background);
		m_pWindow->draw(m_background2);
		for(unsigned int i = 0; i < m_birds.size(); ++i) {
			m_birds[i]->draw(m_pWindow);
		}
		pPlayer->draw(m_pWindow);
		
		if(!m_flyPos.empty() && distance(pPlayer->getSprite()->getPosition(), sf::Vector2f(m_flyPos.front(), pPlayer->getSprite()->getPosition().y)) < 60.0f && (pPlayer->state == pPlayer->WALKING || pPlayer->state == pPlayer->STANDING)) {
			m_flyText.setColor(sf::Color(0,0,0));
			m_flyText.move(0.0f, 1.0f);
			m_pWindow->draw(m_flyText);
			m_flyText.move(0.0f, -2.0f);
			m_pWindow->draw(m_flyText);
			m_flyText.move(1.0f, 1.0f);
			m_pWindow->draw(m_flyText);
			m_flyText.move(-2.0f, 0.0f);
			m_pWindow->draw(m_flyText);
			m_flyText.setColor(sf::Color(255,255,255));
			m_flyText.move(1.0f, 0.0f);
			m_pWindow->draw(m_flyText);
		}else if(pPlayer->getBirdCount() < m_birds.size() && distance(pPlayer->getSprite()->getPosition(),
				m_birds[pPlayer->getBirdCount()]->getSprite()->getPosition()) <
				m_birds[pPlayer->getBirdCount()]->getSprite()->getLocalBounds().width && (pPlayer->state == pPlayer->WALKING || pPlayer->state == pPlayer->STANDING)) {
			m_talkText.setColor(sf::Color(0,0,0));
			m_talkText.move(0.0f, 1.0f);
			m_pWindow->draw(m_talkText);
			m_talkText.move(0.0f, -2.0f);
			m_pWindow->draw(m_talkText);
			m_talkText.move(1.0f, 1.0f);
			m_pWindow->draw(m_talkText);
			m_talkText.move(-2.0f, 0.0f);
			m_pWindow->draw(m_talkText);
			m_talkText.setColor(sf::Color(255,255,255));
			m_talkText.move(1.0f, 0.0f);
			m_pWindow->draw(m_talkText);
		}
	} else {
		for(unsigned int i = 0; i < m_menuObjects.size(); ++i)
			m_pWindow->draw(*m_menuObjects[i]);
	}
	if(m_bChangeState)
		m_pWindow->draw(m_white);
	m_pWindow->display();
}

void Game::clean() {
	for(unsigned int i = 0; i < m_menuObjects.size(); ++i)
		delete m_menuObjects[i];
	m_menuObjects.clear();
}

void Game::initDarkAstronaut() {
	sf::Sprite* pSprite = new sf::Sprite(*TextureManager::Instance()->load("data/gfx/DAG.png", "DAG"));
	pSprite->setOrigin(pSprite->getLocalBounds().width / 2.0f, pSprite->getLocalBounds().height / 2.0f);
	pSprite->setPosition(m_pWindow->getView().getCenter().x, m_pWindow->getView().getCenter().y);
	
	m_menuObjects.push_back(pSprite);
}

void Game::initMainMenu() {
	for(unsigned int i = 0; i < m_menuObjects.size(); ++i)
		delete m_menuObjects[i];
	m_menuObjects.clear();
	
	sf::Sprite* pSprite = new sf::Sprite(*TextureManager::Instance()->load("data/gfx/vollant.png", "vollantlogo"));
	pSprite->setOrigin(pSprite->getLocalBounds().width / 2.0f, pSprite->getLocalBounds().height / 2.0f);
	pSprite->setPosition(m_pWindow->getView().getCenter().x, m_pWindow->getView().getCenter().y - m_pWindow->getView().getSize().y / 7.0f);
	
	m_menuObjects.push_back(pSprite);
	
	sf::Text *pText = new sf::Text("Press SPACE to begin", m_textFont, 60);
	sf::FloatRect textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(m_pWindow->getView().getCenter().x, m_pWindow->getView().getCenter().y + m_pWindow->getView().getSize().y / 2.5f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("#peaceloveandjam", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(41.0f, 155.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("#1buttonjam", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(28.5f, 165.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("#multijam1", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(25.6f, 175.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("@xvix56", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(461.0f, 175.0f);
	
	m_menuObjects.push_back(pText);
	
	m_music.setVolume(35.0f);
	m_music.play();
	
	state = MAINMENU;
}

void Game::initGame() {
	for(unsigned int i = 0; i < m_menuObjects.size(); ++i)
		delete m_menuObjects[i];
	m_menuObjects.clear();
	
	m_music.setVolume(60.0f);
	
	m_background.setTexture(*TextureManager::Instance()->load("data/gfx/meadow.png", "grass"));
	m_background.setPosition(0.0f, 0.0f);
	m_background2.setTexture(*TextureManager::Instance()->getTexture("grass"));
	m_background2.setPosition(m_background.getLocalBounds().width, 0.0f);
	m_flyText.setCharacterSize(40);
	m_flyText.setString("Click SPACE to FLY");
	m_flyText.setFont(m_textFont);
	m_flyText.setScale(0.5f, 0.5f);
	sf::FloatRect textRect = m_flyText.getLocalBounds();
	m_flyText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	m_flyText.setPosition(m_pWindow->getView().getCenter().x, 50.0f);
	
	m_talkText.setCharacterSize(40);
	m_talkText.setString("Click SPACE to TALK");
	m_talkText.setFont(m_textFont);
	m_talkText.setScale(0.5f, 0.5f);
	textRect = m_talkText.getLocalBounds();
	m_talkText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	m_talkText.setPosition(m_pWindow->getView().getCenter().x, 50.0f);
	
	m_flyPos.push_back(400);
	m_flyPos.push_back(770);
	m_flyPos.push_back(1150);
	m_flyPos.push_back(1550);
	m_flyPos.push_back(1950);
	m_flyPos.push_back(2500);
	m_heights.push_back(155.0f);
	m_heights.push_back(140.0f);
	m_heights.push_back(105.0f);
	m_heights.push_back(75.0f);
	m_heights.push_back(50.0f);
	m_heights.push_back(25.0f);
	m_birdsID.push_back("pipit");
	m_birdsID.push_back("ringedplover");
	m_birdsID.push_back("wren");
	m_birdsID.push_back("whinchat");
	m_birdsID.push_back("lapwing");
	m_birdsID.push_back("littleringedplover");
	m_birdsFilenames.push_back("data/gfx/pipit.png");
	m_birdsFilenames.push_back("data/gfx/ringedplover.png");
	m_birdsFilenames.push_back("data/gfx/whinchat.png");
	m_birdsFilenames.push_back("data/gfx/wren.png");
	m_birdsFilenames.push_back("data/gfx/lapwing.png");
	m_birdsFilenames.push_back("data/gfx/littleringedplover.png");
	m_birdTexts.push_back(std::string("Hey Vollant, Did you\nfinally learn how to\nfly? Show me if you can."));
	m_birdTexts.push_back(std::string("I saw that you can't\nfly yet, it's normal for\nyoung birds. Don't worry\nyou will be flying soon,\nyou just have to try harder."));
	m_birdTexts.push_back(std::string("I already thought that\nyou made it, but then\nyou fell. Maybe flying\nisn't for you"));
	m_birdTexts.push_back(std::string("Don't force it, you\ncan do it, but you have\nto do it naturally."));
	m_birdTexts.push_back(std::string("That was amazing, you\njust have to stay\nlonger in the air,\nkeep it up!"));
	m_birdTexts.push_back(std::string("Don't give up,\n you can do it!\nI believe in you!"));
	m_birdsSounds.push_back("data/sounds/iinchadney__wren-in-the-morning.wav");
	m_birdsSounds.push_back("data/sounds/Flussregenpfeifer_-_Little_Ringed_Plover_-_Charadrius_dubius.ogg");
	m_birdsSounds.push_back("data/sounds/Clive_Bramham-Enchanting_song_of_Whinchat_one_blue_morning.ogg");
	m_birdsSounds.push_back("data/sounds/iinchadney__wren-in-the-morning.wav");
	m_birdsSounds.push_back("data/sounds/juskiddink__lapwing.wav");
	m_birdsSounds.push_back("data/sounds/Flussregenpfeifer_-_Little_Ringed_Plover_-_Charadrius_dubius.ogg");
	
	pPlayer = new Player(*TextureManager::Instance()->getTexture("lark"), sf::Vector2f(100.0f, 180.0f), sf::IntRect(0, 0, 58, 51));
	pPlayer->setWalkingTexture(TextureManager::Instance()->load("data/gfx/larkwalking.png", "larkwalking"), sf::IntRect(0, 0, 62, 51), 6);
	pPlayer->setFlyingTexture(TextureManager::Instance()->load("data/gfx/larkflying.png", "larkflying"), sf::IntRect(0, 0, 71, 110), 4, sf::IntRect(0, 41, 71, 32));
	m_prevPos = pPlayer->getSprite()->getPosition().x;
	std::list<int>::iterator it = m_flyPos.begin();
	for(unsigned int i = 0; i < m_flyPos.size(); ++i, ++it) {
		m_birds.push_back(new Bird(*TextureManager::Instance()->load(m_birdsFilenames.front(), m_birdsID.front()),
					sf::Vector2f((float)(*it - 100), pPlayer->getSprite()->getPosition().y + pPlayer->getSprite()->getOrigin().y - TextureManager::Instance()->getTexture(m_birdsID.front())->getSize().y / 2.0f),
					sf::IntRect(0, 0, 0, 0),
					m_birdTexts.front(),
					m_textFont,
					m_birdsSounds.front()));
		m_birdsID.push_back(m_birdsID.front());
		m_birdsID.pop_front();
		m_birdsFilenames.push_back(m_birdsFilenames.front());
		m_birdsFilenames.pop_front();
		m_birdTexts.push_back(m_birdTexts.front());
		m_birdTexts.pop_front();
		m_birdsSounds.push_back(m_birdsSounds.front());
		m_birdsSounds.pop_front();
	}
	bird_state = NORMAL;
	state = GAME;
}

void Game::initExit() {
	m_music.setVolume(35.0f);
	
	m_pWindow->setView(sf::View(sf::FloatRect(0.0f, 0.0f, m_pWindow->getDefaultView().getSize().x * 0.5f, m_pWindow->getDefaultView().getSize().y * 0.5f)));

	sf::Sprite* pSprite = new sf::Sprite(*TextureManager::Instance()->getTexture("vollantlogo"));
	pSprite->setOrigin(pSprite->getLocalBounds().width / 2.0f, pSprite->getLocalBounds().height / 2.0f);
	pSprite->setPosition(m_pWindow->getView().getCenter().x, m_pWindow->getView().getCenter().y - m_pWindow->getView().getSize().y / 7.0f);
	
	m_menuObjects.push_back(pSprite);
	
	sf::Text *pText = new sf::Text("Press SPACE to exit", m_textFont, 60);
	sf::FloatRect textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(m_pWindow->getView().getCenter().x, m_pWindow->getView().getCenter().y + m_pWindow->getView().getSize().y / 2.5f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("#peaceloveandjam", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(41.0f, 155.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("#1buttonjam", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(28.5f, 165.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("#multijam1", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(25.6f, 175.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("@xvix56", m_textFont, 30);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(461.0f, 175.0f);
	
	m_menuObjects.push_back(pText);
	
	pText = new sf::Text("sounds, music and fonts has their credits files in data directories", m_textFont, 24);
	textRect = pText->getLocalBounds();
	
	pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	pText->setColor(sf::Color(0, 0, 0));
	pText->setScale(0.25f, 0.25f);
	pText->setPosition(m_pWindow->getView().getCenter().x, 176.0f);
	
	m_menuObjects.push_back(pText);

	state = EXIT;
}

float Game::distance(sf::Vector2f pt1, sf::Vector2f pt2) {
	sf::Vector2f tmp(pt1.x - pt2.x, pt1.y - pt2.y);

	return sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
}