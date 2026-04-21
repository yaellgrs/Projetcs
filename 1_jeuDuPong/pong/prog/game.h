#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define SCREEN_WIDTH 800
#define SPEED 2.5f
#define MAX_VERSUS_SCORE 5


int ballplay(sf::CircleShape& ball, sf::RectangleShape ping, sf::RectangleShape& pong, float& x, float& y);

void player1(sf::RectangleShape& ping);

void player2(sf::RectangleShape& pong);

void game(sf::RenderWindow& window, sf::RectangleShape& ping, sf::RectangleShape& pong, sf::CircleShape& ball, sf::Text text);

void Init(sf::CircleShape& ball, sf::RectangleShape& ping, sf::RectangleShape& pong);

void InitSpeed(float& x, float& y);
