#pragma once
#include <SFML/Graphics.hpp>
#include <random>

#include "ball.h"
#include "Consts.h"
#include "PowerUp.h"

enum GameMode {
	menu,
	play, 
	over
};

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	//int statut = 0;
	GameMode mode = GameMode::menu;
	//menu
	sf::Texture menuTx;
	sf::Sprite menuSp;

	sf::Font font;
	sf::Text Txt_balls;

	//Game over
	sf::Texture overTx;
	sf::Sprite overSp;
	//player
	sf::Sprite barre;
	sf::Texture barreTex;
	//balle
	//Ball ball;
	std::vector<Ball*>balls;
	//brick
	std::vector<sf::RectangleShape*>bricks;
	std::vector<PowerUp*> powerUps;

	bool KeyReleased = true;


	//init
	void initWindow();
	void initMenu();
	void initOver();
	void initPlayer();
	void initBall();
	void initBrick();
	void initTexts();

public:
	Game();

	//update
	void update();
	void upPlayer();
	void upBall();
	void upGame();
	void upTexts();

	//render
	void render();
	void renderMenu();
	void renderOver();

	void run();
};