#include "PowerUp.h"

void PowerUp::InitSprite()
{
	if (!this->texture.loadFromFile("img/newBall.png")) printf("can't Load newBalle.png\n");
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(texture);
	this->sprite->setScale(0.1f, 0.1f);
}

PowerUp::PowerUp(float x, float y)
{
	this->posX = x;
	this->posY = y;

	InitSprite();
}

void PowerUp::Update()
{
	this->posY += GRAVITY_FORCE * SPEED;

	sprite->setPosition(this->posX, this->posY);
}

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target = window
	target.draw(*sprite);
}
