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
	int maxHeight = 5;
	int maxWidth = 10;

	for (int i = 0; i < maxHeight; i++) {

		for (int j = 0; j < maxWidth; j++) {
			float gutter = 5.f;
			float sizeX = ((SCREEN_WIDTH - gutter) / maxWidth) - gutter;
			float sizeY = (( (SCREEN_HEIGHT * 0.3f) -gutter) / maxHeight) - gutter;
			// 1 - 0 - 1 - 0 - 1
			//width = gutter + (size+gutter)*n
			// (width - gutter)/n) - gutter ) size;
			//((width - gutter)/n)-gutter = size+gutter


			sf::RectangleShape* brick = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
			brick->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
			brick->setPosition(gutter + (sizeX + gutter) * j, gutter + (sizeY + gutter) * i);
			bricks.push_back(brick);
		}




	}
	printf("brick size :%d", bricks.size());
}

void Game::initTexts()
{
	font.loadFromFile("img/Thanks.ttf");
	Txt_balls.setFont(font);
	Txt_balls.setString("Balls : 0");
	Txt_balls.setCharacterSize(50);
	float posX = 10;
	float posY = (SCREEN_HEIGHT - Txt_balls.getGlobalBounds().height) / 2;
	Txt_balls.setPosition(posX, posY);
}

Game::Game() {

	initWindow();
	initMenu();
	initOver();
	initPlayer();
	initBall();
	initTexts();
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
	for (int i = 0; i < balls.size();) {

		x = balls[i]->upBall(&bricks, barre);

		if (x == -2) { //ball hors écran 
			balls.erase(balls.begin() + i);
			continue;
		}
		else if (x == 1) { //brick détruite
			if (rand() % 100 < 100) {
				PowerUp* powerUp = new PowerUp(balls[i]->GetPosX(), balls[i]->GetPosY());
				powerUps.push_back(powerUp);
				upTexts();
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

void Game::upTexts()
{
	Txt_balls.setString("Balls :" + std::to_string(balls.size()));
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

	window->draw(Txt_balls);
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


