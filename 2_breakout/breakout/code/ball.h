#pragma once
#include <SFML/Graphics.hpp>
#include <random>

#include "Consts.h"



class Ball {
private:
	sf::CircleShape ball;
	int x;
	int y;
		
	void initBall();
public:
	Ball();
	int upBall(std::vector<sf::RectangleShape>* bricks, sf::Sprite barre);
	sf::CircleShape getBall();
	int getX();
	int getY();
};