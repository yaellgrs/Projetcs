#include "game.h"


void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Breackout");
	window->setFramerateLimit(120);
}

void Game::initMenu() {
	if (!menuTx.loadFromFile("img/menu.jpg")) {
		printf("loading error of menu image\n");
	}
	menuSp.setTexture(menuTx);
}

void Game::initOver() {
	if (!overTx.loadFromFile("img/over.jpg")) {
		printf("loading error of over image\n");
	}
	overSp.setTexture(overTx);
}

void Game::initPlayer() {
	if (!barreTex.loadFromFile("img/barre.png")) {
		printf("loading errror of barre texture\n");
	}
	barre.setTexture(barreTex);
	barre.setPosition(500, 760);
}

void Game::initBall() {
	balls.clear();
	Ball ball;
	balls.push_back(ball);

}

void Game::initBrick() {
	bricks.clear();
	int x = 0;
	for (int i = 0; i < 5; i++) {
		int j = 0;

		while (10 + 60 * j < 1200) {

			sf::RectangleShape brick(sf::Vector2f(50, 20));
			brick.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
			brick.setPosition(5.f + 60.f * j, 10.f + i*30);
			bricks.push_back(brick);
			j++;
			x++;
		}
	}
}

Game::Game() {

	initWindow();
	initMenu();
	initOver();
	initPlayer();
	initBall();
}

/*                ------------------------------
						   	  UPDATE
*/

void Game::update() {
	upPlayer();
	upBall();
	upGame();

}

void Game::upPlayer() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && barre.getPosition().x > 0) {
		barre.move(-10.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && barre.getPosition().x < 990) {
		barre.move(10, 0.f);
	}
}


void Game::upBall() {
	int i = 0;
	bool dba = false;
	bool dbr = false;
	int x = 0;
	for (auto& ball : balls) {
		if (dbr == false) {
			x = ball.upBall(bricks, barre);
		}
		if (x == -2) {
			dba = true;
		}
		else if (x > 0) {
			dbr = true;
			if (rand() % 100 < 25) {
				Ball ball;
				balls.push_back(ball);
			}
		}
		if (dba == false) {
			i++;
		}
	}
	if (dba == true) {
		balls.erase(balls.begin() + i);
	}
	if (dbr == true) {
		bricks.erase(bricks.begin() + x);
	}
	if (balls.size() == 0) {
		statut = 3;
	}
}

void Game::upGame() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window->close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			initPlayer();
			initBrick();
			initBall();
			if (statut == 3) {
				statut = 0;
			}
			else {
				statut = 1;
			}
		}
	}
}

/*		          		     UPDATE
				------------------------------
*/

void Game::render() {
	window->clear();
	window->draw(barre);
	for (auto ball : balls) {
		window->draw(ball.getBall());
	}


	for (auto brick : bricks) {
		window->draw(brick);
	}
	window->display();

}

void Game::renderMenu() {
	window->clear();
	window->draw(menuSp);
	window->display();
}

void Game::renderOver() {
	window->clear();
	window->draw(overSp);
	window->display();
}

void Game::run() {


	while (window->isOpen()) {
		if (statut == 0) {
			upGame();
			renderMenu();
		}
		//a fixer
		else if(statut == 1) {
			update();
			render();
		}
		else {
			upGame();
			renderOver();
		}

	}
}


