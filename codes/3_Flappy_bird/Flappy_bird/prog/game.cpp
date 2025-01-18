#include "game.h"

void Game::initWindow() {
	window = new sf::RenderWindow(sf::VideoMode(1200, 800), "Flappy Bird");
	window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);


}

void Game::initMap() {
	mapUpper.setSize(sf::Vector2f(1200.f, 100.f));
	mapUpper.setFillColor(sf::Color(80, 43, 20, 255));
	
	mapBottom.setSize(sf::Vector2f(1200.f, 100.f));
	mapBottom.setFillColor(sf::Color(80, 43, 20, 255));
	mapBottom.setPosition(sf::Vector2f(0.f, 700.f));
}

void Game::initBird() {
	if (!birdTx.loadFromFile("img/bird.png")) {
		printf("loading error of bird's texture\n");
	}
	birdSp.setTexture(birdTx);
	birdSp.setScale(sf::Vector2f(0.1f, 0.1f));
	birdSp.setPosition(sf::Vector2f(150.f, 375.f));

	birdSpeed = BIRDSPEED;
}

void Game::initPipe() {

	float x = float(rand()%350);//50 400-50;
	sf::RectangleShape pipeU;
	pipeU.setSize(sf::Vector2f(50.f, x));
	pipeU.setPosition(sf::Vector2f(1200.f, 100.f));
	pipeU.setFillColor(sf::Color(90, 150, 40, 255));
	pipesU.push_back(pipeU);
	
	sf::RectangleShape pipeB;
	pipeB.setSize(sf::Vector2f(50.f, 350-x));//
	pipeB.setPosition(sf::Vector2f(1200.f, 700.f-pipeB.getSize().y));
	pipeB.setFillColor(sf::Color(90, 150, 40, 255));
	pipesB.push_back(pipeB);
	
}

void Game::initMenu() {
	state = 0;
	pipesU.clear();
	pipesB.clear();
	initBird();
	initPipe();
	pipeSpeed = -5.f;
	pipeTime = 2.f;
	cpt = 0;


	if (!font.loadFromFile("img/arial.ttf")) {
		printf("loading echec for the font\n");
	}
	start.setFont(font);
	start.setString("S t a r t");
	start.setPosition(450.f, 250.f);
	start.setScale(sf::Vector2f(2.f, 2.f));
	start.setFillColor(sf::Color(255, 255, 255, 100));

	setting.setFont(font);
	setting.setString("S e t t i n g");
	setting.setPosition(400.f, 350.f);
	setting.setScale(sf::Vector2f(2.f, 2.f));
	setting.setFillColor(sf::Color(255, 255, 255, 100));

	exit.setFont(font);
	exit.setString("e x i t");
	exit.setPosition(475.f, 450.f);
	exit.setScale(sf::Vector2f(2.f, 2.f));
	exit.setFillColor(sf::Color(255, 255, 255, 100));

	speed.setFont(font);
	speed.setPosition(400.f, 300.f);
	speed.setScale(sf::Vector2f(2.f, 2.f));

	retour.setFont(font);
	retour.setString("r e t o u r");
	retour.setPosition(425.f, 400.f);
	retour.setScale(sf::Vector2f(2.f, 2.f));

	score.setFont(font);
	score.setPosition(1100.f, 50.f);
	

}

void Game::initOver() {
	menuState = 0;

	endScore.setFont(font);
	endScore.setString("S c o r e :    " + std::to_string(cpt));
	endScore.setScale(sf::Vector2f(2.f, 2.f));
	endScore.setPosition(400.f, 300.f);
	endScore.setFillColor(sf::Color(255, 255, 255, 255));


	endMenu.setFont(font);
	endMenu.setString("M e n u");
	endMenu.setScale(sf::Vector2f(2.f, 2.f));
	endMenu.setPosition(450.f, 400.f);
	endMenu.setFillColor(sf::Color(255, 255, 255, 100));
}


Game::Game() {
	initWindow();
	initMap();
	initBird();
	initPipe();
	initMenu();
}
//updates

void Game::upMenu() {
	upGame();

	std::ostringstream ss;
	ss << std::fixed << std::setprecision(1) << (-pipeSpeed / 2);
	speed.setString("s p e e d : " + ss.str());

	if (menuState == 0) {
		if (!isSetting) {
			
			start.setFillColor(sf::Color(255, 255, 255, 255));
			setting.setFillColor(sf::Color(255, 255, 255, 100));
			exit.setFillColor(sf::Color(255, 255, 255, 100));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				state = 1;
				pipeCl.restart();
			}
		}
		else {
			speed.setFillColor(sf::Color(255, 255, 255, 255));
			retour.setFillColor(sf::Color(255, 255, 255, 100));

		}

	}
	else if (menuState == 1) {
		if (!isSetting) {
			start.setFillColor(sf::Color(255, 255, 255, 100));
			setting.setFillColor(sf::Color(255, 255, 255, 255));
			exit.setFillColor(sf::Color(255, 255, 255, 100));
		}
		else {
			speed.setFillColor(sf::Color(255, 255, 255, 100));
			retour.setFillColor(sf::Color(255, 255, 255, 255));
		}

	}
	else if(menuState == 2) {
		if (!isSetting) {
			start.setFillColor(sf::Color(255, 255, 255, 100));
			setting.setFillColor(sf::Color(255, 255, 255, 100));
			exit.setFillColor(sf::Color(255, 255, 255, 255));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			window->close();
		}
	}
}

void Game::update() {
	upGame();
	upBird();
	upPipes();

	score.setString(" " + std::to_string(cpt));
}

void Game::upGame() {
	while (window->pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			initMenu();

		}

		if (state == 0) {
			//gere le menu principal
			if (!isSetting) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (menuState < 2) {
						menuState++;
					}
					else {
						menuState = 0;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (menuState > 0) {
						menuState--;
					}
					else {
						menuState = 2;
					}
				}
			}
			//gere le menu de setting
			else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (menuState > 0) {
						menuState--;
					}
					else {
						menuState = 1;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (menuState < 1) {
						menuState++;
					}
					else {
						menuState = 0;
					}
				}
				if (menuState == 0) {
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						pipeSpeed -= 1.f;
						pipeTime -= 0.05f;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						if (-pipeSpeed / 2 > 1.f) {
							pipeSpeed += 1.f;
							pipeTime += 0.05f;
						}
					}
				}
			}
			//gere le passage dde setting a retour
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				if (menuState == 1) {
					isSetting = !isSetting;
				}
			}
		}
	}
}


void Game::upBird() {
	sf::FloatRect birdBox = birdSp.getGlobalBounds();
	if (!birdBox.intersects(mapBottom.getGlobalBounds())) {
		birdSp.move(0.f, gravity);
	}
	//move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && move == 0) {
		falling = false;
		birdSp.move(0.f, birdSpeed);
		move++;
		birdSp.rotate(-25);
	}
	if (move > 0 && move <15) {
		birdSp.move(0.f, birdSpeed);
		move++;
		if (move == 14) {
			birdSp.rotate(25);
			move = 0;
		}
	}
	//pipe collision
	for (auto pipe : pipesU) {

		if (birdBox.intersects(pipe.getGlobalBounds())) {
			birdSpeed = 0.f;
			pipeSpeed = 0.f;
			initOver();
			state = 3;
		}
		else if (!passed && birdSp.getPosition().x > pipe.getPosition().x) {
			cpt++;
			passed = true;
			
		}
	}
	for (auto pipe : pipesB) {
		if (birdBox.intersects(pipe.getGlobalBounds())) {
			birdSpeed = 0.f;
			pipeSpeed = 0.f;
		}
	}

}

void Game::upPipes() {
	//pipe du haut 
	bool out = false;
	for (auto& pipe : pipesU) {
		pipe.move(pipeSpeed, 0.f);
		if (pipe.getPosition().x > -50) {
		}
		else {
			out = true;
		}
	}
	if (out == true) {
		pipesU.erase(pipesU.begin());
		out = false;
	}

	//pipe du bas
	out = false;
	for (auto& pipe : pipesB) {
		pipe.move(pipeSpeed, 0.f);
		if (pipe.getPosition().x > -50) {
		}
		else {
			out = true;
		}
	}
	if (out == true) {
		pipesB.erase(pipesB.begin());
		out = false;
		passed = false;
	}
	
	if (pipeCl.getElapsedTime().asSeconds() > pipeTime) {
		initPipe();
		pipeCl.restart();
	}

}


void Game::upOver() {
	while (window->pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			menuState ++;
			if (menuState == 2) {
				menuState = 0;
			}
		}
		if (menuState == 0) {
			endScore.setFillColor(sf::Color(255, 255, 255, 255));
			endMenu.setFillColor(sf::Color(255, 255, 255, 100));

		}
		else if (menuState == 1) {
			endScore.setFillColor(sf::Color(255, 255, 255, 100));
			endMenu.setFillColor(sf::Color(255, 255, 255, 255));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				initMenu();
				state = 0;
			}
		}
	}
}




//render menu
void Game::rendMenu() {
	window->clear();
	if (!isSetting) {
		window->draw(start);
		window->draw(setting);
		window->draw(exit);
	}
	else {
		window->draw(speed);
		window->draw(retour);
	}

	window-> display();
}

//render game
void Game::render() {
	window->clear();
	window->draw(birdSp);
	for (auto pipe : pipesU) {
		window->draw(pipe);
	}
	for (auto pipe : pipesB) {
		window->draw(pipe);
	}

	window->draw(mapUpper);
	window->draw(mapBottom);
	window->draw(score);
	
	window->display();
	
}

void Game::rendOver() {
	window->clear();

	window->draw(endScore);
	window->draw(endMenu);

	window->display();
}

void Game::run() {
	while (window->isOpen()) {

		if (state == 0) {
			upMenu();
			rendMenu();
		}
		else if (state == 1) {
			update();
			render();
		}
		else {
			upOver();
			rendOver();
		}

	}
}
	
	//game over