#include "game.h"

/*
			INIT
*/

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Stickman Fight");
	window->setFramerateLimit(120);
}

void Game::initMap() {
	bottom.setFillColor(sf::Color(75, 75, 75, 255));
	bottom.setSize(sf::Vector2f(1000, 50));
	bottom.setPosition(100, 600);
}

void Game::initPlayer() {
	player1 = new Player(1);
	player2 = new Player(2);
	player1->setBox(bottom.getGlobalBounds());
	player2->setBox(bottom.getGlobalBounds());
}

void Game::initVie() {
	font.loadFromFile("img/arial.ttf");

	vie1Tx.setFont(font);
	vie1Tx.setString(std::to_string(int(player1->getVie())) + " / " + std::to_string(int(player1->getVie())));
	vie1Tx.setPosition(50, 80);
	vie1Tx.setOutlineColor(sf::Color::Black);
	vie1Tx.setOutlineThickness(5.f);

	vie2Tx.setFont(font);
	vie2Tx.setString(std::to_string(int(player2->getVie())) + " / " + std::to_string(int(player2->getVie())));
	vie2Tx.setPosition(750, 80);
	vie2Tx.setOutlineColor(sf::Color::Black);
	vie2Tx.setOutlineThickness(5.f);

	barre1.setSize(sf::Vector2f(400, 50));
	barre1.setPosition(50, 25);
	barre1.setFillColor(sf::Color::Transparent);
	barre1.setOutlineColor(sf::Color::Black);
	barre1.setOutlineThickness(5.f);

	vie1.setSize(sf::Vector2f(400, 50));
	vie1.setPosition(50, 25);
	vie1.setFillColor(sf::Color::Red);

	barre2.setSize(sf::Vector2f(400, 50));
	barre2.setPosition(750, 25);
	barre2.setFillColor(sf::Color::Transparent);
	barre2.setOutlineColor(sf::Color::Black);
	barre2.setOutlineThickness(5.f);

	vie2.setSize(sf::Vector2f(400, 50));
	vie2.setPosition(750, 25);
	vie2.setFillColor(sf::Color::Red);
}

void Game::initMenu() {
	play.setFont(font);
	play.setString(" P l a y");
	play.setCharacterSize(60);
	play.setPosition(500, 200);

	setting.setFont(font);
	setting.setString(" S e t t i n g");
	setting.setCharacterSize(60);
	setting.setPosition(425, 350);

	exit.setFont(font);
	exit.setString(" E x i t");
	exit.setCharacterSize(60);
	exit.setPosition(500, 500);
}

void Game::initOver() {
	lose.setFont(font);
	lose.setCharacterSize(60);
	lose.setPosition(300, 200);

	menu.setFont(font);
	menu.setCharacterSize(60);

	exit2.setFont(font);
	exit2.setCharacterSize(60);
}
/*
			INIT
*/

Game::Game() {
	initWindow();
	initMap();
	initPlayer();
	initVie();
	initMenu();
	
	// a mettre lors de la mort 
	initOver();
}


/*
			UPDATE
*/

void Game::update() {

	if (gameState == 0) {
		upMenu();
	}
	else if(gameState == 1) {
		upGame();
	}
	else {
		upOver();
	}
}

//MENU
void Game::upMenu() {
	while (window->pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (menuState == 2) {
				menuState = 0;
			}
			else {
				menuState++;
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (menuState == 0) {
				menuState = 2;
			}
			else {
				menuState--;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && menuState == 0) {
			initPlayer();
			initVie();

			gameState = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && menuState == 1) {

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && menuState == 2) {
			window->close();
		}

	}


	upPlay();
	upSetting();
	upExit();



}

void Game::upPlay() {
	if (menuState == 0) {


		play.setFillColor(sf::Color::White);
		setting.setFillColor(sf::Color(90, 90, 90, 100));
		exit.setFillColor(sf::Color(90, 90, 90, 100));

		play.setString("-> P l a y <-");
		setting.setString(" S e t t i n g");	
		exit.setString(" E x i t");

		play.setPosition(440, 200);
		setting.setPosition(425, 350);
		exit.setPosition(500, 500);

	}
}

void Game::upSetting() {
	if (menuState == 1) {
		play.setFillColor(sf::Color(90, 90, 90, 100));
		setting.setFillColor(sf::Color::White);
		exit.setFillColor(sf::Color(90, 90, 90, 100));

		play.setString(" P l a y");
		setting.setString("-> S e t t i n g <-");
		exit.setString(" E x i t");

		play.setPosition(500, 200);
		setting.setPosition(365, 350);
		exit.setPosition(500, 500);
	}
}

void Game::upExit() {
	if (menuState == 2) {
		play.setFillColor(sf::Color(90, 90, 90, 100));
		setting.setFillColor(sf::Color(90, 90, 90, 100));
		exit.setFillColor(sf::Color::White);

		play.setString(" P l a y");
		setting.setString(" S e t t i n g");
		exit.setString("-> E x i t <-");

		play.setPosition(500, 200);
		setting.setPosition(425, 350);
		exit.setPosition(440, 500);
	}

}

//GAME

void Game::upGame() {
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}


	player1->upPerso(player2->getFire());
	player2->upPerso(player1->getFire());
	upBarre();
	if (player1->getVie() <= 0 || (player2->getVie() <= 0)) {
		gameState = 2;
	}

}

void Game::upBarre() {
	vie1.setSize(sf::Vector2f(player1->getVie(), 50));
	vie2.setSize(sf::Vector2f((player2->getVie()), 50));
	vie1Tx.setString(std::to_string(int(player1->getVie())) + " / " + std::to_string(int(LIFE)));
	vie2Tx.setString(std::to_string(int(player2->getVie())) + " / " + std::to_string(int(LIFE)));

}

//GAME OVER

void Game::upOver() {
	while (window->pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (overState == 0) {
				overState = 1;
			}
			else {
				overState = 0;
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && overState == 0) {
			gameState = 0;
			menuState = 0;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && overState == 1) {
			window->close();
		}
	}
	upLose();
	
	upMenuOver();
	upExitOver();

}

void Game::upLose() {
	if (player1->getVie() < player2->getVie()) {
		lose.setString("Le joueur " + std::to_string(1) + " a perdu");
	}
	else {
		lose.setString("Le joueur " + std::to_string(2) + " a perdu");
	}



}


void Game::upMenuOver() {
	if (overState == 0) {
		menu.setString("-> M e n u <-");
		menu.setFillColor(sf::Color::White);
		menu.setPosition(420, 350);

		exit2.setString("e x i t");
		exit2.setFillColor(sf::Color(90, 90, 90, 100));
		exit2.setPosition(530, 500);


	}
}

void Game::upExitOver() {
	if(overState == 1) {
		menu.setString("M e n u");
		menu.setFillColor(sf::Color(90, 90, 90, 100));
		menu.setPosition(500, 350);
		
		exit2.setString("-> e x i t <-");
		exit2.setFillColor(sf::Color::White);
		exit2.setPosition(450, 500);
	}
}


/*
			UPDATE
*/

//render
void Game::render() {


	if (gameState == 0) {
		renderMenu();
	}
	else if (gameState == 1) {
		renderGame();
	}
	else {
		renderOver();
	}



}

void Game::renderMenu() {
	window->clear();

	window->draw(play);
	window->draw(setting);
	window->draw(exit);
	window->display();
}

void Game::renderOver() {
	window->clear();

	window->draw(lose);
	window->draw(exit2);
	window->draw(menu);

	window->display();
}

void Game::renderGame() {
	window->clear(sf::Color::Blue);

	renderPlayers();

	window->draw(barre1);
	window->draw(barre2);
	window->draw(vie1);
	window->draw(vie2);
	window->draw(vie1Tx);
	window->draw(vie2Tx);

	window->draw(bottom);

	window->display();
}

void Game::renderPlayers() {
	window->draw(player1->getPerso());
	if (player1->getOnFire()) {
		window->draw(player1->getFire());
	}
	window->draw(player2->getPerso());
	if (player2->getOnFire()) {
		window->draw(player2->getFire());
	}

	window->draw(player1->getName());
	window->draw(player2->getName());
}

void Game::run() {
	while (window->isOpen()) {
		update();
		render();
	}

}