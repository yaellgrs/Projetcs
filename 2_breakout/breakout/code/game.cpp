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

			sf::RectangleShape* brick = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
			brick->setFillColor(sf::Color(255,255,255, 255));
			brick->setPosition(gutter + (sizeX + gutter) * j, TOP_MARGIN + gutter + (sizeY + gutter) * i);
			bricks.push_back(brick);
		}
	}
}

void Game::initHUD()
{
	font.loadFromFile("img/Thanks.ttf");
	T_ball.loadFromFile("img/newBall.png");

	Sp_ball.setTexture(T_ball);
	Sp_ball.setScale(0.065f, 0.065f);
	Sp_ball.setPosition(0, 7);

	Txt_balls.setFont(font);
	Txt_balls.setString("1");
	Txt_balls.setCharacterSize(40);

	Txt_balls.setPosition(
		Sp_ball.getGlobalBounds().width + 5,
		0
	);

	Txt_timer.setFont(font);
	Txt_timer.setString("3");
	Txt_timer.setCharacterSize(100);
	Txt_timer.setPosition(
		(SCREEN_WIDTH - Txt_timer.getGlobalBounds().width) / 2,
		(SCREEN_HEIGHT - Txt_timer.getGlobalBounds().height) / 2
	);

	Txt_stage.setFont(font);
	Txt_stage.setString("stage 1");
	Txt_stage.setCharacterSize(40);
	Txt_stage.setPosition(
		(SCREEN_WIDTH - Txt_stage.getGlobalBounds().width) / 2,
		0
	);
	Txt_score.setFont(font);
	Txt_score.setString("score : 0");
	Txt_score.setCharacterSize(40);
	Txt_score.setPosition(
		(SCREEN_WIDTH - Txt_score.getGlobalBounds().width) - 10,
		0
	);




	Rs_hider = sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	Rs_hider.setFillColor(sf::Color(0, 0, 0, 170));
}


Game::Game() {

	initWindow();
	initMenu();
	initOver();
	initPlayer();
	initBall();
	initHUD();
}

/*                ------------------------------
						   	  UPDATE
*/

void Game::update() {

	upGame();
	if (upTimer()) {
		upPlayer();
		upBall();

	}

	

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
			if (rand() % 100 < POWERUP_PROBABILITIE) {
				PowerUp* powerUp = new PowerUp(balls[i]->GetPosX(), balls[i]->GetPosY());
				powerUps.push_back(powerUp);
				upHUD();
			}

			score += 100;
			if (bricks.size() <= 0) LevelUpStage();
			else upHUD();
			
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
			mode = GameMode::play;
			clock.restart();
			Rs_hider.setFillColor(sf::Color(0, 0, 0, 200));
			Txt_timer.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if (KeyReleased && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			KeyReleased = false;
			LevelUpStage();
		}
		else {
			KeyReleased = true;
		}
	}
}

void Game::upHUD()
{
	Txt_balls.setString(std::to_string(balls.size()));
	Txt_stage.setString("stage " + std::to_string(stage));


	Txt_score.setString("score : " + std::to_string(score));
	Txt_score.setPosition(
		(SCREEN_WIDTH - Txt_score.getGlobalBounds().width) - 10,
		0
	);
}

bool Game::upTimer()
{
		if (clock.getElapsedTime().asSeconds() < 3.f){
			float time = TIMER_START - clock.getElapsedTime().asSeconds();
			Txt_timer.setString(std::to_string((int)time));
			return false;
		}
		else {
			Rs_hider.setFillColor(sf::Color(0, 0, 0, 0));
			Txt_timer.setFillColor(sf::Color(0, 0, 0, 0));
			return true;
		}
}

/*		          		     UPDATE
				------------------------------
*/

void Game::LevelUpStage()
{
	stage++;

	for (Ball* ball : balls) {
		ball->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	initBrick();
	upHUD();

}

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


	window->draw(Sp_ball);
	window->draw(Txt_balls);
	window->draw(Txt_stage);
	window->draw(Txt_score);

	window->draw(Rs_hider);
	window->draw(Txt_timer);
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


