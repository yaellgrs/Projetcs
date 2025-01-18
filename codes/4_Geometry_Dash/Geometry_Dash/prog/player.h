#pragma once
#include <SFML/Graphics.hpp>

#define GRAVITY 8.f
#define SPEED 7.5f



class Player {
private:
	sf::Sprite persoSp;
	sf::Texture persoTx;
	sf::Texture persoJump;
	sf::RectangleShape persoBox;
	//b = bottom R = right
	bool start = false;
	int jump = 0;
	int cptTx = 0;
	bool isJump, onGround;

	void initPerso();
public:
	Player();
	~Player();

	//updates
	void update(std::vector<sf::RectangleShape>& maps, sf::View &view, sf::Sprite &bottom);
	bool collisionBottom(sf::FloatRect box, std::vector<sf::RectangleShape>& maps,  sf::Sprite& bottom);
	bool collisionRight(sf::FloatRect box, std::vector<sf::RectangleShape>& maps, sf::Sprite& bottom);
	
	void restart();

	sf::Sprite getPerso();

};