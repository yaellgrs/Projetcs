#include "game.h"

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Launcher");
	window->setFramerateLimit(120);

	if (!font.loadFromFile("Assets/Thanks.ttf")) {
		printf("loading error of font\n");
	}
	Txt_pong.setFont(font);
	Txt_pong.setCharacterSize(75);
	Txt_pong.setString("Jeu du Pong");
	Txt_pong.setPosition((SCREEN_WIDTH - Txt_pong.getLocalBounds().width) / 2, 20);
}



Game::Game(){
	initWindow();
}
//updates

void Game::update() {
	upGame();
}

void Game::upGame() {
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			if (gameSelected == Project::Pong)
				system("cd Games\\Pong && pong.exe");
		}
	}
}

//render
void Game::render() {
	window->clear();
	window->draw(Txt_pong);
	window->display();
}

void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}

}