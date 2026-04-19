#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "player.h"

#define tileW 40
#define tileH 13


class Game {
private:
	//fenetre
	sf::RenderWindow* window;
	sf::Event event;
	sf::View view;
	//perso
	Player* perso;
	//map
	int map[tileH][tileW];
	sf::Texture mapTx, pikeTx;
	std::vector<sf::Sprite> maps;
	std::vector<sf::RectangleShape>pikeBox;
	sf::Sprite bottomSp;
	sf::Texture bottomTx;


	void initWindow();
	void initMap();
public:
	Game();
	~Game();
	//updates
	void update();
	void upGame();
	//???
	void restart();
	
	//render
	void render();
	void renderGame();
	void drawMap();

	void run();
	//apelle render et update
};