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

PowerUp::~PowerUp()
{
	delete sprite;
}

void PowerUp::Update(sf::Sprite* barre, std::vector<Ball*>* balls)
{
	this->posY += GRAVITY_FORCE * SPEED;

	sprite->setPosition(this->posX, this->posY);
	if (collected) return;

	sf::FloatRect box = sprite->getGlobalBounds();
	if(box.intersects(barre->getGlobalBounds()))
	{
		balls->push_back(new Ball());
		collected = true;
	}
}

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target = window
	target.draw(*sprite);
}
