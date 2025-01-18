#include "Player.h"


/*
				INIT
*/

void Player::initPerso() {
	persoTxRight.loadFromFile("img/walk.png");
	persoSp.setTexture(persoTxRight);
	persoSp.setTextureRect(sf::IntRect(200, 0, 50, 75));
	if (j == 1) {
		persoSp.setPosition(400, 400);
		isRight = true;
		persoSp.setColor(sf::Color::Blue);
	}
	else if (j==2) {
		persoSp.setPosition(800, 400);
		persoSp.setColor(sf::Color::Blue);
		isRight = false;
	}
	
	persoTxLeft.loadFromFile("img/walkLeft.png");
}

void Player::initBall() {
	ballTx.loadFromFile("img/ball.png");
	ballSp.setTexture(ballTx);
}

void Player::initName() {
	font.loadFromFile("img/arial.ttf");

	name.setFont(font);
	if (j == 1) {
		name.setString("J 1");
		name.setFillColor(sf::Color::Red);
	}
	else {
		name.setString("J 2");
		name.setFillColor(sf::Color::Green);
	}

	name.setCharacterSize(25);
	name.setPosition(persoSp.getPosition().x, persoSp.getPosition().y - 50);
}

/*
				INIT
*/



Player::Player(int n) {
	j = n;
	initPerso();
	initBall();
	initName();

}



/*
			UPDATE
*/

void Player::upPerso(sf::Sprite otherBall) {
	gravity();
	walk();
	jump();
	fire();
	upVie(otherBall);

	name.setPosition(persoSp.getPosition().x, persoSp.getPosition().y - 50);
}

void Player::upPersoTx() {
	if (texture == 1) {
		persoSp.setTextureRect(sf::IntRect(0, 0, 50, 75));
	}
	else if (texture == 2) {
		persoSp.setTextureRect(sf::IntRect(50, 0, 50, 75));
	}
	else if (texture == 3) {
		persoSp.setTextureRect(sf::IntRect(100, 0, 50, 75));
	}
	else if (texture == 4) {
		persoSp.setTextureRect(sf::IntRect(150, 0, 50, 75));
	}
	else if (texture == 5) {
		persoSp.setTextureRect(sf::IntRect(200, 0, 50, 75));
	}
	else if (texture == 6) {
		persoSp.setTextureRect(sf::IntRect(250, 0, 50, 75));
	}
}

void Player::upVie(sf::Sprite otherBall) {
	sf::FloatRect box = persoSp.getGlobalBounds();

	if (box.intersects(otherBall.getGlobalBounds()) &&
		vieCl.getElapsedTime() >= sf::seconds(0.4)) {

		vieCl.restart();

		vie -= 50;
		
		
	}
}

/*
			UPDATE
*/

void Player::gravity() {
	sf::FloatRect boxPlayer = persoSp.getGlobalBounds();
	if (!bottomBox.intersects(boxPlayer) && !isJump) {
		persoSp.move(0, GRAVITY);
		onGround = false;
	}
	else if (!isJump) {
		onGround = true;
	}

	if (persoSp.getPosition().y > 900){
		vie -= 50;
		persoSp.setPosition(600, 100);
	}
}

void Player::walk() {
	if (j == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isWalk == false) {
			isWalk = true;
			isRight = true;
			walkCl.restart();
			stay = 5;
			persoSp.setTexture(persoTxRight);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && isWalk == false) {
			isWalk = true;
			isRight = false;
			walkCl.restart();
			stay = 2;
			persoSp.setTexture(persoTxLeft);
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isWalk == false) {
			isWalk = true;
			isRight = true;
			walkCl.restart();
			stay = 5;
			persoSp.setTexture(persoTxRight);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isWalk == false) {
			isWalk = true;
			isRight = false;
			walkCl.restart();
			stay = 2;
			persoSp.setTexture(persoTxLeft);
		}
	}




	if (isWalk && (walkCl.getElapsedTime() >= sf::seconds(0.015f))) {
		walkCl.restart();
		if (texture == 6) {
			texture = 1;
		}
		else {
			texture++;
		}

		if (isRight) {
			persoSp.move(9.f, 0);
		}
		else {
			persoSp.move(-9.f, 0);
		}
		upPersoTx();
		if (texture == stay) {
			isWalk = false;
		}
	}
}

void Player::jump() {
	if (j == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && onGround == true) {
			isJump = true;
			onGround = false;
			jumpCl.restart();
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround == true) {
			isJump = true;
			onGround = false;
			jumpCl.restart();
		}
	}



	if (isJump && jumpCl.getElapsedTime() <= sf::seconds(0.25)) {
		if (isRight) {
			texture = 3;
			upPersoTx();
		}
		else {
			texture = 4;
			upPersoTx();
		}
		persoSp.move(0, -7);
	}
	else if (!isWalk) {
		isJump = false;
		if (isRight) {
			texture = 5;
			upPersoTx();
		}
		else {
			texture = 2;
			upPersoTx();
		}
	}
}

void Player::fire() {
	if (j == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !onFire) {
			printf("space\n");
			onFire = true;
			fireCl.restart();
			if (!isRight) {
				coef = -1;
			}
			else {
				coef = 1;
			}

			ballSp.setPosition(persoSp.getPosition().x + (coef * 20), persoSp.getPosition().y);
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && !onFire) {
			printf("space\n");
			onFire = true;
			fireCl.restart();

			if (!isRight) {
				coef = -1;
			}
			else {
				coef = 1;
			}

			ballSp.setPosition(persoSp.getPosition().x + (coef * 20), persoSp.getPosition().y);
		}
	}


	if (onFire && fireCl.getElapsedTime() < sf::seconds(0.5)) {
		ballSp.move(coef*10	, 0);
	}
	else {
		onFire = false;
		ballSp.setPosition(-100, -100);
	}


}



void Player::setBox(sf::FloatRect box) {
	bottomBox = box;
}

sf::Sprite Player::getPerso() {
	return persoSp;
}

sf::Sprite Player::getFire() {
	return ballSp;
}

bool Player::getOnFire() {
	return onFire;
}

float Player::getVie() {
	return vie;
}

sf::Text Player::getName() {
	return name;
}