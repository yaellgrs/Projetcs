#pragma once

#include <SFML/Graphics.hpp>

#include "Consts.h"
#include "Ball.h"

class PowerUp : public sf::Drawable {
public:
	const float SPEED = 0.25f;


public:
	float posX;
	float posY;

	bool collected = false;

	sf::Texture texture;
	sf::Sprite* sprite;


private:
	void InitSprite();


public:
	PowerUp(float x, float y);
	~PowerUp();
	
	void Update(sf::Sprite* barre, std::vector<Ball*>* balls);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};