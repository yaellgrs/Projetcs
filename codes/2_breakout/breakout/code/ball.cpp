#include "ball.h"

void Ball::initBall() {
	ball.setRadius(10.f);
	ball.setPosition(580, 600);
	x = -SPEED;
	y = -SPEED;
}


Ball::Ball() {
	initBall();
}


//retourner un bricks ? 
int Ball::upBall(std::vector<sf::RectangleShape>bricks, sf::Sprite barre) {
		
		sf::FloatRect ballBox = ball.getGlobalBounds();
		int i = 0;
		for (auto& brick : bricks) {
			if (ballBox.intersects(brick.getGlobalBounds())) {
				y = -y;

				ball.move(x, y);
				return i;
			}
			i++;
		}

		if (ballBox.intersects(barre.getGlobalBounds())) {
			y = -y;
			if (rand() % 100 < 25) {
				ball.setFillColor(sf::Color(155, 155.f, 0.f, 100.f));
				x *= 1.5;
				y *= 1.5;
			}
		}
		else if (ball.getPosition().y > 778) {
			ball.move(x, y);
			return -2;
			
		}
		else if (ball.getPosition().y < 2) {
			y = -y;
		}
		else if (ball.getPosition().x > 1188 || ball.getPosition().x < 2) {
			x = -x;
		}

		ball.move(x, y);
		return -1;

}


sf::CircleShape Ball::getBall() {
	return ball;
}

int Ball::getX() {
	return x;
}

int Ball::getY() {
	return y;
}