#include "game.h"

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1280, 832), "Geometry Dash");
	window->setVerticalSyncEnabled(true);
	view.setSize(1280, 832);
	view.move(150, 0);

}

void Game::initMap() {
	std::ifstream fichier { "img/map.txt" };

	for (int i = 0; i < tileH; i++) {
		for (int j = 0; j < tileW; j++) {
			fichier >> map[i][j];
		}
	}
	fichier.close();

	if (!mapTx.loadFromFile("img/tile_1.png")) {
		printf("Loading error of Texture of the tile 1.");
	}
	pikeTx.loadFromFile("img/pike.png");
	for (int i = 0; i < tileH; i++) {
		for (int j = 0; j < tileW; j++) {
			if (map[i][j] == 1) {
				sf::Sprite tile;
				tile.setTexture(mapTx);
				tile.setScale(2, 2);
				tile.setPosition(j * 64, i * 64);
				maps.push_back(tile);

				sf::RectangleShape box(sf::Vector2f(tile.getGlobalBounds().width, tile.getGlobalBounds().height));
				box.setPosition(tile.getPosition().x, tile.getPosition().y);
				box.setOutlineColor(sf::Color(255, 241, 125, 100));
				box.setOutlineThickness(2.f);
				pikeBox.push_back(box);
			}	
			if (map[i][j] == 2) {
				sf::Sprite tile;
				tile.setTexture(pikeTx);
				tile.setPosition(j * 64, i * 64);
				maps.push_back(tile);
				
				sf::RectangleShape box(sf::Vector2f(tile.getGlobalBounds().width, tile.getGlobalBounds().height));
				box.setOutlineColor(sf::Color(255, 241, 125, 100));
				box.setOutlineThickness(2.f);
				box.scale(0.25, 0.5);
				box.setPosition(tile.getPosition().x+24, tile.getPosition().y+16);
				pikeBox.push_back(box);
			}
		}
	}

	bottomTx.loadFromFile("img/sol.png");
	bottomSp.setTexture(bottomTx);
	bottomSp.setPosition(0, 832);
}


Game::Game() {
	initWindow();
	initMap();
	perso = new Player;
}
Game::~Game() {
	if (perso) {
		delete perso;
		perso = nullptr;
	}
}
//updates

void Game::update() {
	upGame();
	if (perso && !maps.empty()) {  // Vérifie que perso n'est pas nul et maps contient des éléments
		perso->update(pikeBox, view, bottomSp);
	}
}

void Game::upGame() {
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			view.move(100.f, 0);
		}
	}
}

void Game::restart() {
	initMap();
	perso = new Player;
	view.setCenter(640, 512);
}

//render
void Game::render() {
	window->setView(view);

	window->clear(sf::Color::Blue);
	renderGame();

	window->display();
}
void Game::renderGame() {
	if (perso != NULL) {
		window->draw(perso->getPerso());
	}




	drawMap();
}

void Game::drawMap() {
	for (auto tile : maps) {
		window->draw(tile);
	}
	window->draw(bottomSp);
}

void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}

}