#include "monster.h"


void Monster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(monsterSp);
}



void Monster::initMonster() {

	monsterSp.setTextureRect(sf::IntRect(0, 0, 64, 64));
	int y = tile / tileW;
	int x = tile % tileW;
	monsterSp.setPosition(x * 64, y * 64);
}

Monster::Monster(int tileSpawn) {
	tile = tileSpawn;
	initMonster();

}

void Monster::loadMap(int map[]) {
	for (int i = 0; i < tileH * tileW; i++) {
		level[i] = map[i];
	}
}

void Monster::loadTexture(sf::Texture &texture) {
	monsterSp.setTexture(texture);
}


void Monster::update(Player &player) {
	if (kill) {
		monsterSp.move(0, 2);
	}
	else {
		gravity();
		sf::Vector2f pos;
		if (monsterDirection > 0) { // DROITE
			pos = sf::Vector2f(monsterSp.getPosition().x + 64, monsterSp.getPosition().y);
		}
		else {  //GAUCHE
			pos = sf::Vector2f(monsterSp.getPosition().x, monsterSp.getPosition().y);
		}

		if (!player.collision(pos)) {
			monsterSp.move(2 * monsterDirection, 0);
			if (textCl.getElapsedTime() > sf::seconds(0.1)) {
				monsterTxSet++;
				textCl.restart();
			}

		}
		else {
			monsterDirection *= -1;
		}

	}

	if (monsterTxSet == 4) {
		monsterTxSet = 1;
	}

	if (player.collMonster(monsterSp)) {
		kill = true;
	}

	updateTx();

}

void Monster::gravity() {

	int posx = int((monsterSp.getPosition().x) / 64);
	int posx2 = int((monsterSp.getPosition().x + 60) / 64);
	int posy = int((monsterSp.getPosition().y + 66) / 64);

	int tile = (posx)+(tileW * (posy));
	int tile2 = (posx2)+(tileW * (posy));

		if (level[tile] == 0 && level[tile2] == 0) {
			monsterSp.move(0, 8);
		}

}


void Monster::updateTx() {
	if (monsterTxSet == 1) {
		monsterSp.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
	else if (monsterTxSet == 2) {
		monsterSp.setTextureRect(sf::IntRect(64, 0, 64, 64));

	}
	else if (monsterTxSet == 3) {
		monsterSp.setTextureRect(sf::IntRect(128, 0, 64, 64));
	}
}

bool Monster::isDead() {
	if (monsterSp.getPosition().y > 640) {
		return true;
	}
	return false;
}