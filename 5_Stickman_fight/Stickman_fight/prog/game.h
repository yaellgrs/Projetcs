#pragma once

#include "Player.h"

#define GRAVITY 5.f

class Game {
private:
	//fenetre
	sf::RenderWindow* window;
	sf::Event event;
	int gameState = 0;

	sf::RectangleShape bottom;

	//menu
	sf::Text play, setting, exit;
	int menuState = 0;

	//game over menu
	sf::Text menu, exit2, lose;
	int overState = 0;

	//joueurs
	Player* player1;
	Player* player2;

	//vie
	sf::RectangleShape barre1;
	sf::RectangleShape vie1;
	sf::RectangleShape barre2;
	sf::RectangleShape vie2;

	//texte
	sf::Font font;
	sf::Text vie1Tx, vie2Tx;

	void initWindow();
	void initMap();
	void initPlayer();
	void initVie();
	void initMenu();
	void initOver();
public:
	Game();
	//updates

	void upMenu();
	void upPlay();
	void upSetting();
	void upExit();

	void update();
	void upGame();
	void upBarre();

	void upOver();
	void upLose();
	void upMenuOver();
	void upExitOver();

	
	//render
	void render();
	void renderMenu();
	void renderOver();
	void renderGame();
	void renderPlayers();

	void run();
};