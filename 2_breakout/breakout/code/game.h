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

	//timer
	sf::Clock clock;
	sf::RectangleShape Rs_hider;

	//HUD
	sf::Font font;
	sf::Texture T_ball;
	sf::Sprite Sp_ball;

	sf::Text Txt_balls;
	sf::Text Txt_stage;
	sf::Text Txt_timer;
	sf::Text Txt_score;


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

public:
	int stage = 0;
	int score = 0;

	bool KeyReleased = true;


	//init
	void initWindow();
	void initMenu();
	void initOver();
	void initPlayer();
	void initBall();
	void initBrick();
	void initHUD();



public:
	Game();

	//update
	void update();
	void upPlayer();
	void upBall();
	void upGame();
	void upHUD();
	bool upTimer();

	//fonctions

	void LevelUpStage();

	//render
	void render();
	void renderMenu();
	void renderOver();

	void run();
};