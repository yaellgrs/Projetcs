#include "Player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	/*sf::FloatRect box = persoSp.getGlobalBounds();
	sf::RectangleShape boxdra;
	boxdra.setSize(sf::Vector2f(box.width, box.height));
	boxdra.setOutlineColor(sf::Color::Black);
	boxdra.setOutlineThickness(2.f);
	boxdra.setFillColor(sf::Color::Transparent);
	boxdra.setPosition(persoSp.getPosition());


	target.draw(boxdra);*/
	target.draw(persoSp);
}

/*
			INIT
*/

void Player::initPerso() {
	persoTxRight.loadFromFile("img/perso.png");
	persoTxLeft.loadFromFile("img/persoLeft.png");
	
	isRight = true,
	persoTxSet = 1;
	upPersoTx();
	persoSp.setPosition(128, 64);

	persoBounds = persoSp;
}

/*
			INIT
*/

Player::Player() {
	initPerso();

}

void Player::loadMap(const int* tiles) {
	for (int i = 0; i < tileH*tileW; i++) {
		map[i] = tiles[i];
	}
}

bool Player::collision(sf::Vector2f position) {
	//calcul the number of the tile's player	
	/*
	HG   HD

	BG   BD
	*/
	int x = int(position.x / 64);
	int y = int(position.y / 64);

	int tileHG = int((position.x) / 64) + (tileW * int((position.y + 4) / 64));
	int tileHD = int((position.x + 60) / 64) + (tileW * int((position.y + 4) / 64));
	int tileBG = (int((position.x) / 64)) + (tileW * int((position.y + 60) / 64));

	//pour detecter que les tile au dessus du persos
	int tileJG = int((position.x + 32) / 64) + (tileW * int((position.y - 4) / 64));



	if (isJump) {
		if (map[tileJG] != 0) {
			jumpTile = tileJG;
			return true;
		}

	}

	if (map[tileHG] != 0) {
		return true;

	}
	else if (map[tileBG] != 0) {
		return true;
	}
	else if (map[tileHD] != 0 && isJump) {
		if (isJump) {
			jumpTile = tileHD;
		}
		return true;
	}
	else if (position.x <= -16) {
		return true;
	}

	jumpTile = -1;


	return false;
}

/*
				UPDATE
*/


void Player::update(sf::View& view){



	if (firstGround) {
		persoBounds.setPosition(persoSp.getPosition());
		upInput();
		upMove(view);
		upPersoTx();
	}
	else {
		gravity();
	}


}
void Player::upInput() {
	if (!isWalk) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (!isRight) {
				isWalk = true;
			}
			else {
				isRight = false;
				walkCl.restart();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (isRight) {
				isWalk = true;
			}
			else {
				isRight = true;
				walkCl.restart();
			}

		}
	}
	else {
		isWalk = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround) {;
		onGround = false;
		jumpCl.restart();
		isJump = true;
	}
}
void Player::upMove(sf::View& view) {

	gravity();
	if (!isDead) {
		jump();
		walk(view);
	}


	
}

void Player::gravity() {

	int posx = int((persoSp.getPosition().x) / 64);
	int posx2 = int((persoSp.getPosition().x+60) / 64);
	int posy = int((persoSp.getPosition().y+66) / 64);

	int tile = (posx)+(tileW * (posy));
	int tile2 = (posx2)+(tileW * (posy));
	if (!isDead) {
		if (map[tile] != 0 || map[tile2] != 0 && !isJump) {

			onGround = true;
			if (!firstGround) {
				firstGround = true;
			}
		}
		else if (!isJump) {
			onGround = false;
			persoBounds.move(0, 6);
			persoSp.move(0, 6);
		}
	}
	else {
		if (deadClock.getElapsedTime() < sf::seconds(0.1)) {
			persoSp.move(-2, -2);
		}
		else if(deadClock.getElapsedTime() < sf::seconds(1)) {
			persoSp.move(0, 0);
			if (persoSp.getRotation() != 270) {
				persoSp.rotate(-10);
			}
		}
		else {
			persoSp.move(0, 4);

		}

	}

}


void Player::walk(sf::View& view) {
	if ((isWalk) && walkCl.getElapsedTime() > sf::seconds(0.025)) {
		if (isRight) {
			persoBounds.move(64, 0);


			if (!collision(persoBounds.getPosition())) {
				persoSp.move(16, 0);
				if (persoSp.getPosition().x > 600) {
					view.move(16, 0);
				}

			}
			else {
				persoBounds.setPosition(persoSp.getPosition());
			}
			persoTxSet++;

		}
		else {
			persoBounds.move(-16, 0);
			if (!collision(persoBounds.getPosition())) {
				persoSp.move(-16, 0);
				if (persoSp.getPosition().x > 600) {
					view.move(-16, 0);
				}
			}
			else {
				persoBounds.setPosition(persoSp.getPosition());
			}
			persoTxSet++;
		}
		walkCl.restart();
	}
	if (persoTxSet == 5 && isWalk){
		persoTxSet = 1;
	}

}

void Player::jump() {

	if (isJump && jumpCl.getElapsedTime() < sf::seconds(0.20)) {
		persoBounds.move(0, -8);

		if (!collision(persoBounds.getPosition())) {
			persoSp.move(0, -8);
		}
		else {
			isJump = false;
		}

	}
	else if (isJump && jumpCl.getElapsedTime() < sf::seconds(0.5)) {
		persoSp.move(0, -2);
	}
	else {
		isJump = false;
	}

	if (isJump) {
		persoTxSet = 6;
	}
	else if(persoTxSet > 5) {
		persoTxSet = 1;
	}

}


bool Player::collMonster(sf::Sprite &monster) {

	/*
			Il Faudrait gerer ça directement dans la class monstre pour que ça marche mieux 
	*/
	if (monster.getGlobalBounds().intersects(persoSp.getGlobalBounds()) && !isDead) {
		if (monster.getPosition().y - 50 > persoSp.getPosition().y ) {
			isJump = true;
			jumpCl.restart();
			return true;
		}
		else {
			isDead = true;
			deadClock.restart();
		}
	}
	return false;
}

void Player::upPersoTx() {
	if (isRight) {
		persoSp.setTexture(persoTxRight);
	}
	else {
		persoSp.setTexture(persoTxLeft);
	}

	if (persoTxSet == 1) {
		persoSp.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
	else if (persoTxSet == 2) {
		persoSp.setTextureRect(sf::IntRect(64, 0, 64, 64));

	}
	else if (persoTxSet == 3) {
		persoSp.setTextureRect(sf::IntRect(128, 0, 64, 64));
	}
	else if (persoTxSet == 6) {
		persoSp.setTextureRect(sf::IntRect(192, 0, 64, 64));
	}
}


/*
				UPDATE
*/

int Player::getJumpTile() {
	return jumpTile;
}

float Player::getPosx() {
	return persoSp.getPosition().x;
}