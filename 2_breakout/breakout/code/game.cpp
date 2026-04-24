#include "game.h"


void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT	), "Breakout");
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
	int posY = SCREEN_HEIGHT - barre.getGlobalBounds().height;
	int posX = (SCREEN_WIDTH - barre.getGlobalBounds().width) /2;
	barre.setPosition(posX, posY);
}

void Game::initBall() {
	balls.clear();
	Ball* ball = new Ball();
	balls.push_back(ball);

}

void Game::initBrick() {
	bricks.clear();
	int x = 0;
	for (int i = 0; i < 5; i++) {
		int j = 0;

		while (10 + 60 * j < 1200) {

			sf::RectangleShape* brick = new sf::RectangleShape(sf::Vector2f(50, 20));
			brick->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
			brick->setPosition(5.f + 60.f * j, 10.f + i*30);
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

	for (PowerUp* powerUp : powerUps) {
		powerUp->Update(&barre, &balls);
	}
	powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(), [](const PowerUp* pow) { return pow->collected; }), powerUps.end());


}

void Game::upPlayer() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && barre.getPosition().x > 0) {
		barre.move(-10.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && barre.getPosition().x < (SCREEN_WIDTH - barre.getGlobalBounds().width)) {
		barre.move(10, 0.f);
	}
}


void Game::upBall() {
	int x = 0;
	printf("---------\n");
	for (int i = 0; i < balls.size();) {

		printf("ball : %d posx: %f, posy: %f\n", i, balls[i]->GetPosX(), balls[i]->GetPosY());

		x = balls[i]->upBall(&bricks, barre);

		if (x == -2) { //ball hors écran 
			balls.erase(balls.begin() + i);
			continue;
		}
		else if (x == 1) { //brick détruite
			if (rand() % 100 < 100) {
				PowerUp* powerUp = new PowerUp(balls[i]->GetPosX(), balls[i]->GetPosY());
				powerUps.push_back(powerUp);
			}
		}
		i++;
	}
	if (balls.empty())
		mode = GameMode::over;
}

void Game::upGame() {
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		else if (KeyReleased && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			KeyReleased = false;
			if (mode == GameMode::menu)
				window->close();
			else
				mode = GameMode::menu;
		}
		else if (KeyReleased && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			KeyReleased = false;
			initPlayer();
			initBrick();
			initBall();
			if (mode == GameMode::over) {
				mode = GameMode::menu;
			}
			else {
				mode = GameMode::play;
			}
		}
		else {
			KeyReleased = true;
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
		window->draw(ball->getBall());
	}


	for (auto brick : bricks) {
		window->draw(*brick);
	}

	for (PowerUp* powerUp : powerUps) {
			window->draw(*powerUp);
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
		if (mode == GameMode::menu) {
			upGame();
			renderMenu();
		}
		//a fixer
		else if(mode == GameMode::play) {
			update();
			render();
		}
		else {//over
			upGame();
			renderOver();
		}

	}
}


