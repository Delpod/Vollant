#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	Game::Instance()->init(sf::VideoMode(960, 360), "Vollant", sf::Style::Titlebar | sf::Style::Close);
	while(Game::Instance()->isRunning()) {
		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->draw();
	}
	Game::Instance()->clean();
	return 0;
}