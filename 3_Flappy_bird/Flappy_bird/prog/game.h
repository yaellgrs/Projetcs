#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <random>

#define BIRDSPEED -13.f

class Game {
private:
	sf::RenderWindow* window;
	sf::Event event;
	//map
	sf::RectangleShape mapUpper;
	sf::RectangleShape mapBottom;
	//pipes
	sf::Clock pipeCl;
	float pipeSpeed = -5.f;
	float pipeTime = 2.f;
	std::vector<sf::RectangleShape> pipesU;
	std::vector<sf::RectangleShape> pipesB;
	//bird
	int move = 0;
	float birdSpeed;
	float gravity = 7.f;
	bool falling = false;
	sf::Sprite birdSp;
	sf::Texture birdTx;
	//score
	sf::Text score;
	int cpt = 0;
	bool passed = false;
	/*state
	0 = menu
	1 = game 
	2 = game over
	*/
	int state = 0;
	//menu
	sf::Font font;
	sf::Text start, setting, exit;
	sf::Text speed, retour;
	int menuState;
	bool isSetting = false;
	//over
	sf::Text endScore, endMenu;


	void initWindow();
	void initMap();
	void initBird();
	void initPipe();
	void initMenu();
	void initOver();

public:
	Game();
	//updates menu
	void upMenu();
	//updates game
	void update();
	void upGame();
	void upBird();
	void upPipes();
	//updates over
	void upOver();
	

	//render menu
	void rendMenu();
	//render game
	void render();
	//render over
	void rendOver();

	void run();
};