#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>

#define tileW 40
#define tileH 10


enum class move {
	none,
	Up,
	Down,
	Left,
	Right
};

class Player : public sf::Drawable{
private:
	//perso
	sf::Texture persoTxRight, persoTxLeft;
	sf::Sprite persoSp;
	sf::Sprite persoBounds;
	sf::Clock deadClock;
	int persoTxSet;
	int cpt;
	bool isDead = false;
	bool firstGround = false;

	//map
	int map[tileH*tileW];

	//move
	sf::Clock walkCl, jumpCl;
	bool isWalk = false, isJump = false, onGround;
	bool first;
	int x, y;
	int jumpTile;

	//monster
	bool kill;

	bool isRight;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void initPerso();

public:
	Player();

	void loadMap(const int* tiles);
	bool collision(sf::Vector2f position);


	void update(sf::View& view);

	void upInput();

	void upMove(sf::View& view);
	void gravity();
	void walk(sf::View& view);
	void jump();

	bool collMonster(sf::Sprite &monster);
	void upPersoTx();

	int getJumpTile();
	float getPosx();

};
