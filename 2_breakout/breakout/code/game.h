#pragma once
#include <SFML/Graphics.hpp>
#include <random>

#include "ball.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	int statut = 0;
	//menu
	sf::Texture menuTx;
	sf::Sprite menuSp;
	//Game over
	sf::Texture overTx;
	sf::Sprite overSp;
	//player
	sf::Sprite barre;
	sf::Texture barreTex;
	//balle
	//Ball ball;
	std::vector<Ball>balls;
	//brick
	std::vector<sf::RectangleShape>bricks;


	//init
	void initWindow();
	void initMenu();
	void initOver();
	void initPlayer();
	void initBall();
	void initBrick();

public:
	Game();

	//update
	void update();
	void upPlayer();
	void upBall();
	void upGame();

	//render
	void render();
	void renderMenu();
	void renderOver();

	void run();
};