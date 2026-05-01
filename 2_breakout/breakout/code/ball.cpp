#include "ball.h"

void Ball::initBall() {
	ball.setRadius(10.f);
	ball.setPosition(SCREEN_HEIGHT/2, SCREEN_WIDTH / 2);	
	x = -SPEED;
	y = -SPEED;
}


Ball::Ball() {
	initBall();
}


//retourner un bricks ? 
int Ball::upBall(std::vector<sf::RectangleShape*>* bricks, sf::Sprite barre) {
		
		sf::FloatRect ballBox = ball.getGlobalBounds();
		int i = 0;
		for (auto& brick : *bricks) {
			if (ballBox.intersects(brick->getGlobalBounds())) {
				y = -y;

				ball.move(x, y);
				bricks->erase(bricks->begin() + i);
				return 1;
			}
			i++;
		}

		if (ballBox.intersects(barre.getGlobalBounds())) {
			y = -y;
			if (rand() % 100 < 25) {
				ball.setFillColor(sf::Color(255.f, 255.f, 255.f));
			}
		}
		else if (ball.getPosition().y > SCREEN_HEIGHT - ballBox.height) {
			//ball.move(x, y);
			return -2;
			
		}
		else if (ball.getPosition().y < 2) {
			y = -y;
		}
		else if (ball.getPosition().x > SCREEN_WIDTH - ballBox.width || ball.getPosition().x < ballBox.width) {
			x = -x;
		}

		ball.move(x, y);
		return -1;

}


sf::CircleShape Ball::getBall() {
	return ball;
}

float Ball::GetPosX() {
	return this->ball.getPosition().x;
}

float Ball::GetPosY() {
	return this->ball.getPosition().y;
}