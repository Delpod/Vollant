#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Bird.h"

typedef unsigned long int Uint32;

class Game {
public:
	static Game* Instance() {
		if(s_pInstance == nullptr)
			s_pInstance = new Game();
		return s_pInstance;
	}
	
	void init(sf::VideoMode vm, std::string windowName, Uint32 style = sf::Style::Default);
	void handleEvents();
	void update();
	void draw();
	void clean();
	
	bool isRunning() { return m_bRunning; }
	
	void initDarkAstronaut();
	void initMainMenu();
	void initGame();
	void initExit();
	
	Player* getPlayer() { return pPlayer; }
	std::vector<Bird*>* getBirds() { return &m_birds; }
private:
	Game() : m_add(0.0f), m_flyCount(0), m_bChangeState(false) {}
	float distance(sf::Vector2f pt1, sf::Vector2f pt2);
	sf::RenderWindow* m_pWindow;
	sf::Music m_music;
	sf::Font m_logoFont;
	sf::Font m_textFont;
	sf::Text m_flyText;
	sf::Text m_talkText;
	sf::Sprite m_background;
	sf::Sprite m_background2;
	sf::Clock m_clock;
	sf::Clock m_clock2;
	sf::Time m_time;
	sf::RectangleShape m_white;
	sf::Color m_whiteColor;
	std::vector<sf::Drawable*> m_menuObjects;
	std::vector<Bird*> m_birds;
	std::list<std::string> m_birdsID;
	std::list<std::string> m_birdsFilenames;
	std::list<std::string> m_birdsSounds;
	std::list<int> m_flyPos;
	std::list<std::string> m_birdTexts;
	std::list<float> m_heights;
	Player* pPlayer;
	float m_add;
	float m_prevPos;
	unsigned int m_flyCount;
	unsigned int m_stateToDo;
	unsigned int m_way;
	bool m_bRunning;
	bool m_keyPressed;
	bool m_bChangeState;
	enum { DARKASTRONAUT, MAINMENU, GAME, EXIT, DEFEXIT } state;
	enum { NORMAL, ENDFLY } bird_state;
	static Game* s_pInstance;
};

#endif // GAME_H