#pragma once
#include <SFML/Graphics.hpp>

#define GRAVITY 5.f
#define LIFE 400.f


class Player {

private:
	//perso

	sf::Sprite persoSp;
	sf::Texture persoTxRight, persoTxLeft;
	int stay = 5;
	int texture = 5;
	int coef = 1; // tire a droite si 1, sinon a gauche
	float vie = LIFE;
	int j;
	bool first;
	bool isRight;
	bool isWalk = false;
	bool isJump = false;
	bool onGround = false;
	bool onFire = false;

	sf::Text name;
	sf::Font font;
	sf::Clock walkCl, jumpCl, fireCl, vieCl;

	//bottom
	sf::FloatRect bottomBox;

	//ball
	sf::Sprite ballSp;
	sf::Texture ballTx;



	void initPerso();
	void initBall();
	void initName();

public:
	Player(int n);


	void upPerso(sf::Sprite otherBall);
	void upPersoTx();
	void upVie(sf::Sprite otherBall);

	void gravity();
	void walk();
	void jump();
	void fire();

	void setBox(sf::FloatRect box);


	sf::Sprite getPerso();
	sf::Sprite getFire();
	bool getOnFire();
	float getVie();
	sf::Text getName();
	


};