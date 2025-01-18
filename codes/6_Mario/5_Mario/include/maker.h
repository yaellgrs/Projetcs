#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Tilemap.h"

#define tileW 40
#define tileH 10

class Maker :public sf::Drawable{
private:

	//map
	int level[tileW * tileH];
	TileMap map;
	sf::Texture tilemap;
	sf::View viewMap;
	int left = 0;

	//curseur
	sf::RectangleShape cursor;
	int tile = 0;
	sf::Sprite tileSp;
	sf::Texture tileTx;
	int x, y;


	//fonctions 
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	void initMap();
	void initCursor();
public:
	Maker();

	void update(sf::RenderWindow* window, sf::Event& event);
	void updateTx();
	void saveMap();


};