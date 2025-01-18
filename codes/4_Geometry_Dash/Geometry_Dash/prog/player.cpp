#include "player.h"

/*
				INIT
*/


void Player::initPerso() {
	if (!persoTx.loadFromFile("img/perso.png")) {
		printf("Loading error for the perso Texture.\n");
	}
	persoSp.setTexture(persoTx, true);
	persoSp.setScale(2.f, 2.f);
	persoSp.setPosition(100, 500);

}	

/*
				INIT
*/

Player::Player() {
	initPerso();
}
Player::~Player() {

}

void Player::update(std::vector<sf::RectangleShape>& maps, sf::View &view, sf::Sprite& bottom) {
	//initialision de la box du perso 
	persoBox.setSize(sf::Vector2f(persoSp.getGlobalBounds().width, persoSp.getGlobalBounds().height));
	persoBox.setPosition(persoSp.getPosition().x, persoSp.getPosition().y);

	//gravité
	if (!collisionBottom(persoBox.getGlobalBounds(), maps, bottom) && jump == 0) {
		persoSp.move(0, GRAVITY);
		onGround = false;

	}
	else{
		if (!start) { start = true;}
		onGround = true;
	}

	//avancer
	if (start && !collisionRight(persoBox.getGlobalBounds(), maps, bottom)) {
		if (jump > 0){
			persoSp.move(SPEED, -12);
		}
		else {
			persoSp.move(SPEED, 0);

		}
		view.move(SPEED, 0);
		bottom.move(SPEED, 0);
	}

	//sauter
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jump == 0 && onGround) {
		jump = 1;
		cptTx++;
	}
	if (jump > 0) {
		if (jump % 2 == 0) {
			cptTx++;
			printf("%d\n", cptTx);
		}
		if (cptTx != 0 && cptTx != 16) {
			persoTx.loadFromFile("img/jump/perso" + std::to_string(cptTx) + ".png");
			persoSp.setTexture(persoTx, true);
		}

		jump++;
	}
	if (jump > 15) {
		jump = 0;
	}
	if (cptTx > 15) {
		cptTx = 0;
		persoTx.loadFromFile("img/perso.png");
		persoSp.setTexture(persoTx, true);
	}
}



bool Player::collisionBottom(sf::FloatRect box, std::vector<sf::RectangleShape>& maps, sf::Sprite& bottom) {
	if (box.top + box.height + 2>= bottom.getPosition().y) {
		printf("collision bottom ( spm ) \n");
		return true;
	}

	for (auto tile : maps) {
		if (box.top + box.height >= tile.getGlobalBounds().top) {
			if (box.intersects(tile.getGlobalBounds())) {
				printf("collision bottom ( tile ) \n");
				return true;

			}
			
		}
		
	}
	return false;
}

bool Player::collisionRight(sf::FloatRect box, std::vector<sf::RectangleShape>& maps, sf::Sprite& bottom) {

	for (auto tile : maps) {

		if ( (box.left + box.width +SPEED >= tile.getGlobalBounds().left)
			&& (box.top >= tile.getGlobalBounds().top)
			&& (box.top <= tile.getGlobalBounds().top + tile.getGlobalBounds().height)) {
				//printf("%d %d\n", (box.top <= tile.getGlobalBounds().top),  tile.getGlobalBounds().height));
				printf("collision right ( tile ) \n");
				return true;
		}
	}


	return false;
}

void Player::restart() {
	initPerso();
	/*
	start = false;
	int jump = 0;
	int cptTx = 0;
	bool isJump = false;*/
}

sf::Sprite Player::getPerso() {
	return persoSp;
}