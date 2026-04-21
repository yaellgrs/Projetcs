#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

enum Project {
	Pong
};

class Game {
private:
	sf::RenderWindow* window;
	sf::Event event;

	Project gameSelected = Project::Pong;

private:
	sf::Font font;
	sf::Text Txt_pong;


private:
	void initWindow();
public:
	Game();
	//updates
	void update();
	void upGame();
	
	//render
	void render();

	void run();
};