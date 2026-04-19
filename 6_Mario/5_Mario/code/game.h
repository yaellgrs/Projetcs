#pragma once
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "Player.h"
#include "monster.h"
#include "maker.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>


class Game {
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::View view;

	int gameState = 1;
	//menu
	sf::Font font;
	sf::Sprite menuSp, cursor;
	sf::Texture menuTx, cursorTx;
	sf::Text play, maker, exit;
	int menuState = 1;

	//map
	int level[tileW * tileH];
	TileMap map;
	sf::Texture tilemap;
	sf::Sprite* tileSp, *tileSp2;
	int tilex = 20; 
	int tilex2 = 0;

	//perso
	Player* player;

	//monster
	std::vector<Monster>monsters;
	sf::Texture monsterTx;

	//maker
	Maker mapMaker;

	void initWindow();
	void initView();
	void initMenu();
	void initMap();
	void initPlayer();
	void initMonster();

	void initMaker();
	

public:
	Game();
	~Game();

	//updates
	void update();
	void upMenu();

	void upGame();
	void upMap();
	void upTile1(int tile);
	void upTileSp1();
	void upTile2(int tile);
	void upTileSp2();
	void upMonster();

	void upMaker();

	
	//render
	void render();
	void renderMenu();
	void renderGame();

	void run();
};