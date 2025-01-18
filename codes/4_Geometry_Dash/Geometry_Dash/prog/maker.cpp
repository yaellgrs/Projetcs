#include "maker.h"


void Maker::loadMap() {
	std::ifstream fichier{ "img/map.txt" };

	for (int i = 0; i < tileH; i++) {
		for (int j = 0; j < tileW; j++) {
			fichier >> map[i][j];
		}
	}
	fichier.close();
}

/*
				INIT
*/

void Maker::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1280, 832), "Map maker");
}

void Maker::initMap() {
	focus.setFillColor(sf::Color::Transparent);
	focus.setOutlineColor(sf::Color::Black);
	focus.setOutlineThickness(5.f);
	focus.setSize(sf::Vector2f(64, 64));


	videTx.loadFromFile("img/vide.png");
	mapTx.loadFromFile("img/tile_1.png");
	pikeTx.loadFromFile("img/pike.png");
	maps.clear();
	for (int i = 0; i < tileH; i++) {
		for (int j = 0; j < tileW; j++) {
			if (map[i][j] == 0) {
				sf::Sprite tile;
				tile.setTexture(videTx);
				tile.setPosition(j * 64, i * 64);
				maps.push_back(tile);
			}
			else if (map[i][j] == 1) {
				sf::Sprite tile;
				tile.setTexture(mapTx);
				tile.setScale(2, 2);
				tile.setPosition(j * 64, i * 64);
				maps.push_back(tile);
			}
			else if (map[i][j] == 2) {
				sf::Sprite tile;
				tile.setTexture(pikeTx);
				tile.setPosition(j * 64, i * 64);
				maps.push_back(tile);
			}
		}
	}

	bottomTx.loadFromFile("img/sol.png");
	bottomSp.setTexture(bottomTx);
	bottomSp.setPosition(0, 832);
}

void Maker::initText() {
	font.loadFromFile("img/Thanks.ttf");

	vide.setFont(font);
	vide.setCharacterSize(20);
	vide.setString("A - Block  vide");
	vide.setFillColor(sf::Color::Red);

	block.setFont(font);
	block.setCharacterSize(20);
	block.setPosition(0, 25);
	block.setString("Z - Block  vide");

	pike.setFont(font);
	pike.setCharacterSize(20);
	pike.setPosition(0, 50);
	pike.setString("E - Block  vide");
}

/*
				INIT
*/


void Maker::saveMap() {
	std::ofstream fichier{ "img/map.txt" };

	for (int i = 0; i < tileH; i++) {
		for (int j = 0; j < tileW; j++) {
			fichier << map[i][j] << " ";
		}
	}

}




Maker::Maker() {
	loadMap();

	initWindow();
	initMap();
	initText();
}


/*
				UPDATE
*/

void Maker::update() {
	upEvent();
	upMap();
}

void Maker::upMap() {
	x = (sf::Mouse::getPosition(*window).x)/64;
	y = (sf::Mouse::getPosition(*window).y)/64;

	focus.setPosition(x*64, y*64);
}

void Maker::upEvent() {
	while (window->pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			saveMap();
			window->close();
		}
		else if (event.type == sf::Event::Closed) {
			saveMap();
			window->close();
		}
		//Text
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			vide.setFillColor(sf::Color::Red);
			block.setFillColor(sf::Color::White);
			pike.setFillColor(sf::Color::White);
			make = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			vide.setFillColor(sf::Color::White);
			block.setFillColor(sf::Color::Red);
			pike.setFillColor(sf::Color::White);
			make = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			vide.setFillColor(sf::Color::White);
			block.setFillColor(sf::Color::White);
			pike.setFillColor(sf::Color::Red);
			make = 2;
		}
		//Mouse Click
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (make == 0) {
				printf("click\n");
				map[y][x] = 0;
			}
			else if (make == 1) {
				map[y][x] = 1;
			}
			else if (make == 2) {
				map[y][x] = 2;
			}
			initMap();
		}

	}
}


/*
				UPDATE
*/


void Maker::render() {
	window->clear(sf::Color::Blue);
	drawMap();

	window->draw(vide);
	window->draw(block);
	window->draw(pike);
	window->display();
	
}


void Maker::drawMap() {
	for (auto tile : maps) {
		window->draw(tile);
	}
	window->draw(bottomSp);
	window->draw(focus);
}

void Maker::run() {
	while (window->isOpen()) {
		update();
		render();
	}
}