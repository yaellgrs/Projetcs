#pragma once

#include <SFML/Graphics.hpp>

#include "Consts.h"

class PowerUp : public sf::Drawable {
public:
	const float SPEED = 0.25f;


public:
	float posX;
	float posY;

	sf::Texture texture;
	sf::Sprite* sprite;


private:
	void InitSprite();


public:
	PowerUp(float x, float y);
	
	void Update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};