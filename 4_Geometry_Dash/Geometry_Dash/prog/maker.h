#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#define tileW 40
#define tileH 13

class Maker {

private:
	sf::RenderWindow* window;
	sf::Event event;

	//map
	int map[tileH][tileW];
	sf::Texture videTx, mapTx, pikeTx;
	std::vector<sf::Sprite> maps;
	std::vector<sf::RectangleShape>pikeBox;
	sf::Sprite bottomSp;
	sf::Texture bottomTx;
	sf::RectangleShape focus;
	//text
	sf::Text vide, block, pike;
	sf::Font font;
	int x, y;
	int make = 0;


	void loadMap();
	void initWindow();
	void initMap();
	void initText();

	void saveMap();
public:
	Maker();

	void update();
	void upMap();
	void upEvent();


	void render();
	void drawMap();
	void run();


};