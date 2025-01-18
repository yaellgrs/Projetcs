#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
	sf::RenderWindow window;
	sf::Event event;

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