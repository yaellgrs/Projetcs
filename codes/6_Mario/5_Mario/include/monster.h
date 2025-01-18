#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"


#define tileW 40
#define tileH 10

class Monster : public sf::Drawable{

private:
	sf::Sprite monsterSp;
	sf::Texture monsterTx;
	sf::Clock textCl;
	int tile; 
	int monsterDirection = -1;
	int monsterTxSet = 1;
	int level[tileW * tileH];
	bool kill = false;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
	void initMonster();
public:
	Monster(int tileSpawn);

	void loadMap(int map[]);
	void loadTexture(sf::Texture &texture);

	void update(Player &player);
	void gravity();
	void updateTx();

	bool isDead();


};