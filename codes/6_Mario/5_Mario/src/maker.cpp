#include "maker.h"


void Maker::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(map);
	target.draw(cursor);
	target.draw(tileSp);
}


void Maker::initMap() {
	std::ifstream fichier{ "img/map.txt" };

	tilemap.loadFromFile("img/tile.png");

	for (int i = 0; i < tileH * tileW; i++) {
		fichier >> level[i];

	}
	fichier.close();

	map.load("img/tile.png", sf::Vector2u(64, 64), level, tileW, tileH);
	viewMap.reset(sf::FloatRect(0, 0, 1280, 640));
	//viewMap.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.85f));
}

void Maker::initCursor() {
	cursor.setSize(sf::Vector2f(64, 64));
	cursor.setPosition(-100, -100);
	cursor.setFillColor(sf::Color::Transparent);
	cursor.setOutlineColor(sf::Color::Black);
	cursor.setOutlineThickness(5.f);

	tileTx.loadFromFile("img/tile.png");
	tileSp.setTexture(tileTx);
}

Maker::Maker() {
	initMap();
	initCursor();
}

void Maker::update(sf::RenderWindow* window, sf::Event& event) {
	window->setView(viewMap);
	x = int(sf::Mouse::getPosition(*window).x / 64) + left;
	y = int(sf::Mouse::getPosition(*window).y / 64);
	int pos = x + y * tileW;

	cursor.setPosition(x * 64, y * 64);
	tileSp.setPosition(x * 64, y * 64);

	while (window->pollEvent(event)) {
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			level[pos] = tile;
			map.load("img/tile.png", sf::Vector2u(64, 64), level, tileW, tileH);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && left > 0) {
			viewMap.move(-64, 0);
			left--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && left < 21) {
			viewMap.move(64, 0);
			left++;
		}
		//molette de la souris
		if (event.type == sf::Event::MouseWheelScrolled) {
			if (event.mouseWheelScroll.delta > 0) {
				if (tile != 11) {
					tile++;
				}
				else {
					tile = 0;
				}
			}
			else if (event.mouseWheelScroll.delta < 0) {
				if (tile != 0) {
					tile--;
				}
				else {
					tile = 11;
				}
			}
		}
	}
	updateTx();

}

void Maker::updateTx() {
	if (tile < 10) {
		tileSp.setTextureRect(sf::IntRect(tile*64, 0, 64, 64));
	}
	else {
		tileSp.setTextureRect(sf::IntRect(0, 64, 64, 64));
	}

}

void Maker::saveMap() {
	std::ofstream fichier{ "img/map.txt" };

	for (int i = 0; i < tileH * tileW; i++) {
		fichier << level[i] << " ";
	}
}

