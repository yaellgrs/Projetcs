#include "game.h"

/*
			INIT
*/

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1280, 640), "Mario");
	window->setFramerateLimit(120);

}

void Game::initView() {
	view.reset(sf::FloatRect(0, 0, 1280, 640));
	window->setView(view);
}

void Game::initMenu() {
	font.loadFromFile("img/Minecraft.ttf");
	menuTx.loadFromFile("img/menu.png");
	menuSp.setTexture(menuTx);

	play.setFont(font);
	play.setPosition(600, 175);
	play.setString("P l a y");
	
	maker.setFont(font);
	maker.setPosition(580, 250);
	maker.setString("M a k e r");

	exit.setFont(font);
	exit.setPosition(600, 325);
	exit.setString("E x i t");


	cursorTx.loadFromFile("img/menuCurso.png");
	cursor.setTexture(cursorTx);

}

void Game::initMap() {
	std::ifstream fichier{ "img/map.txt" };

	tilemap.loadFromFile("img/tile.png");

	for (int i = 0; i < tileH*tileW; i++) {
			fichier >> level[i];

	}
	fichier.close();

	map.load("img/tile.png", sf::Vector2u(64, 64), level, tileW, tileH);
}

void Game::initPlayer() {
	player = new Player;
	player->loadMap(level);
}

void Game::initMonster() {
	monsterTx.loadFromFile("img/monster1.png");
	monsters.clear();
	for (int i = 0; i < tileH*tileW; i++) {
		if (level[i] == 10) {
			Monster monster(i);
			monster.loadTexture(monsterTx);
			monster.loadMap(level);
			monsters.push_back(monster);
			level[i] = 0;
		}
	}

}

void Game::initMaker() {
	//maker.load();
}

/*
			INIT
*/


Game::Game() {
	initWindow();
	initMenu();
	initMap();
	initMonster();
	initPlayer();
}
//updates

void Game::update() {
	if (gameState == 1) {
		upMenu();
	}
	else if (gameState == 2) {
		upGame();
		upMap();
		upTileSp1();
		upTileSp2();
		upMonster();
		player->update(view);
		window->setView(view);
	}
	else if (gameState == 3) {
		upMaker();
	}

}

void Game::upMenu() {
	while (window->pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			menuState--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			menuState++;
		}

		if (menuState == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				gameState = 2;
				initMap();
				initMonster();
				initPlayer();
				initView();
			}
		}
		else if (menuState == 2) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				gameState = 3;
			}
		}
		else if (menuState == 3) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				window->close();
			}
		}
	}
	if (menuState == 4) {
		menuState = 1;
	}
	else if (menuState == 0) {
		menuState = 3;
	}

	if (menuState == 1) {
		cursor.setPosition(play.getPosition().x - 40, play.getPosition().y);
	}
	else if (menuState == 2) {
		cursor.setPosition(maker.getPosition().x - 40, maker.getPosition().y);
	}
	else if (menuState == 3) {
		cursor.setPosition(exit.getPosition().x - 40, exit.getPosition().y);
	}
		
	
}

void Game::upGame() {
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			gameState = 1;
			initMenu();
			initView();
		}
		
	}
}

Game::~Game() {
	delete tileSp;
	delete tileSp2;
	monsters.clear();
	delete window;
}

/*
				UPDATES
*/

void Game::upMap() {
	int tile = player->getJumpTile();
	if (tile > 0) {
		if (level[tile] == 1) {
			level[tile] = 9; 
			upTile1(tile);
		}
		else if (level[tile] == 2) {
			level[tile] = 9;
			upTile2(tile);
		}
	}
	map.load("img/tile.png", sf::Vector2u(64, 64), level, tileW, tileH);
	player->loadMap(level);

}

void Game::upTile1(int tile) {

	tileSp = new sf::Sprite;
	tileSp->setTexture(tilemap);
	tileSp->setTextureRect(sf::IntRect(512, 0, 64, 64));
	int y = tile / tileW;
	int x = tile % tileW;
	tileSp->setPosition(x*64, y*64);

	
}

void Game::upTileSp1() {
	if (tileSp != nullptr) {
		if (tilex > 0) {
			tileSp->move(0, -2);
			tilex -= 2;
		}
		else if (tilex2 < 20) {
			tileSp->move(0, 2);
			tilex2 += 2;
		}
		else {
			int x = int(tileSp->getPosition().x / 64);
			int y = int(tileSp->getPosition().y / 64);
			level[x + (y * tileW)] = 8;
			delete tileSp;
			tilex = 20;
			tilex2 = 0;
			tileSp = nullptr;

		}
	}
}

void Game::upTile2(int tile) {
	tileSp2 = new sf::Sprite;
	tileSp2->setTexture(tilemap);
	tileSp2->setTextureRect(sf::IntRect(128, 0, 64, 64));
	int y = tile / tileW;
	int x = tile % tileW;
	tileSp2->setPosition(x * 64, y * 64);
}

void Game::upTileSp2() {
	if (tileSp2 != nullptr) {
		if (tilex > 0) {
			tileSp2->move(0, -2);
			tilex -= 1;
		}
		else if (tilex2 < 20) {
			tileSp2->move(0, 2);
			tilex2 += 1;
		}
		else {
			int x = int(tileSp2->getPosition().x / 64);
			int y = int(tileSp2->getPosition().y / 64);
			level[x + (y * tileW)] = 0;
			delete tileSp2;
			tilex = 20;
			tilex2 = 0;
			tileSp2 = nullptr;
		}
	}
}

void Game::upMonster() {
	 std::vector<int> deadMonsters;

	int dead = -1;
	int i = 0;
	for (auto &monster : monsters) {
		monster.update(*player);
		if (monster.isDead()) {
			dead = i;
		}
		i++;
	}
	if (dead != -1) {
		monsters.erase(monsters.begin() + dead);

	}
}

void Game::upMaker() {
	mapMaker.update(window, event);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		mapMaker.saveMap();
		gameState = 1;
		initView();
	}
}

/*
				UPDATES
*/


//render
void Game::render() {
	window->clear(sf::Color::Blue);
	if (gameState == 1) {
		renderMenu();
	}
	else if (gameState == 2) {
		renderGame();
	}
	else if (gameState == 3) {
		window->draw(mapMaker);
	}


	window->display();
}

void Game::renderMenu() {
	window->draw(menuSp);
	//bouttons
	window->draw(play);
	window->draw(maker);
	window->draw(exit);
	window->draw(cursor);
}

void Game::renderGame() {
	window->draw(map);
	if (tileSp != nullptr) {
		window->draw(*tileSp);
	}
	if (tileSp2 != nullptr) {
		window->draw(*tileSp2);
	}

	for (auto monster : monsters) {
		window->draw(monster);
	}

	window->draw(*player);
}


void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}

}