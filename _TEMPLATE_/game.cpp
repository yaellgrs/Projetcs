#include "game.h"

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Flappy Bird");
	window->setFramerateLimit(120);
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
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
}

//render
void Game::render() {
	window->clear();

	window->display();
}

void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}

}