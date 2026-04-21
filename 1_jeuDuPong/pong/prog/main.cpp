#include "game.h"
#include <fstream>
#include <algorithm>
#include <iostream>*
#include <sstream>
#include <iomanip>


enum GameMode {
    menu,
    normal,
    versus,
    over
};

int main()
{
    bool backMenu = false;


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, 600), "Jeu du Pong");

    //players
    sf::RectangleShape ping(sf::Vector2f(20.f, 200.f));


    //players 2
    sf::RectangleShape pong(sf::Vector2f(20.f, 200.f));

    pong.setFillColor(sf::Color(255, 0, 232, 255));

    //ball
    sf::CircleShape ball(10.f);


    Init(ball, ping, pong);

    //menu
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("img/menu.jpg")) {
        printf("loading error of menu\n");
    }
    sf::Sprite menu;
    menu.setTexture(menuTexture);

    //Game Over
    sf::Texture overTexture;
    if (!overTexture.loadFromFile("img/Over.jpg")) {
        printf("loading error of over\n");
    }
    sf::Sprite over;
    over.setTexture(overTexture);

    sf::Texture T_newRecord;
    if (!T_newRecord.loadFromFile("img/newRecord.jpg")) {
        printf("loading error of new record\n");
    }
    sf::Sprite Sp_newRecord;
    Sp_newRecord.setTexture(T_newRecord);

    //score
    sf::Font font;
    if(!font.loadFromFile("img/Thanks.ttf")){
        printf("loading error of font\n");
    }
    sf::Text Txt_score;
    Txt_score.setFont(font);
    Txt_score.setCharacterSize(75);
    Txt_score.setString("0 - 0");
    Txt_score.setPosition((SCREEN_WIDTH - Txt_score.getLocalBounds().width) / 2, 20);

    sf::Text Txt_speed;
    Txt_speed.setFont(font);
    Txt_speed.setCharacterSize(75);
    Txt_speed.setString("speed : 1.1");
    Txt_speed.setPosition((SCREEN_WIDTH - Txt_speed.getLocalBounds().width) / 2, 30 + Txt_score.getLocalBounds().height);



    int normalScore = 0;
    int playerScore1 = 0;
    int playerScore2 = 0;
    

    //son pong
    sf::SoundBuffer pongbuffer;
    if (!pongbuffer.loadFromFile("img/pong.wav")) {
        printf("loafing error for pongbuffer\n");
    }
    sf::Sound pongSound;
    pongSound.setBuffer(pongbuffer);
    
    //son ping
    sf::SoundBuffer pingbuffer;
    if (!pingbuffer.loadFromFile("img/ping.wav")) {
        printf("loafing error for pingbuffer\n");
    }
    sf::Sound pingSound;
    pingSound.setBuffer(pingbuffer);


    float x = SPEED, y = SPEED;
    window.setFramerateLimit(120);

    GameMode gameMode = GameMode::menu;

    std::fstream f_record;

	f_record.open("img/record.txt", std::ios::in | std::ios::out);
    int record = 0;

    if (!f_record.is_open()) {

        std::ofstream o_record("img/record.txt");
        o_record << "0";;

        printf("création du fichier record\n");

        o_record.close();
    }

    f_record >> record;
    f_record.close();
    
    sf::Clock clock;
    while (window.isOpen())
    {   
        if (2 > ball.getPosition().x || ball.getPosition().x > 778) {

            if (gameMode == GameMode::normal) {
                x = 0.f;
                y = 0.f;
            }
            else {
                InitSpeed(x, y);
            }

            if (2 > ball.getPosition().x) {
                playerScore2++;
                Init(ball, ping, pong);
                InitSpeed(x, y);
                x *= 2;
            }
            else {
                playerScore1++;
				Init(ball, ping, pong);
                InitSpeed(x, y);
                x *= 2;
            }

            
            if(!backMenu && ( gameMode == GameMode::normal || std::max(playerScore1, playerScore2) >= MAX_VERSUS_SCORE)) gameMode = GameMode::over;
        }

        if(gameMode == GameMode::normal)
            Txt_score.setString(std::to_string(normalScore) + " - " + std::to_string(record));
        else if (gameMode == GameMode::versus)
            Txt_score.setString(std::to_string(playerScore1) + " - " + std::to_string(playerScore2));
        
        float speed = std::max(std::abs(x), std::abs(y));
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << (speed - 1 ) ;
		Txt_speed.setString("speed : " + oss.str());
        
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                    window.close();
            }
            if (gameMode == GameMode::menu && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) {
                gameMode = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ? GameMode::normal: GameMode::versus;
                ball.setPosition(390, 290);
                pong.setPosition(775.f, 200.f);
                ping.setPosition(5.f, 200.f);
                InitSpeed(x, y);

                if (normalScore > record)
                {
                    record = normalScore;
                    std::ofstream out("img/record.txt", std::ios::trunc);
                    out << record;
                    out.close();
                    printf("new record : %d\n", record);
                }
                normalScore = 0;;
                playerScore1 = 0;
				playerScore2 = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (gameMode == GameMode::menu)
                {
                    printf("close");
                    window.close();
                }
                else
                    backMenu = true;
            }
            else if(backMenu){
                gameMode = GameMode::menu;
                backMenu = false;
                Init(ball, ping, pong);
			}   
        }  

        if (gameMode == GameMode::menu){
            window.clear();
            window.draw(menu);
            window.display();
        }
        else if (gameMode == GameMode::over) {
            window.clear();
            if (normalScore > record)
                window.draw(Sp_newRecord);
            else
                window.draw(over);
            window.display();
        }
        else {
            int n = ballplay(ball, ping, pong, x, y);
            if ( n > 0 ) {
                if(gameMode == GameMode::normal) normalScore++; 
                if (n == 1) {
                    pingSound.play();
                }
                else {
                    pongSound.play();
                }

 
            }
            player1(ping);
            player2(pong);
            game(window, ping, pong, ball, Txt_score, Txt_speed);
        }

        

    }


    return 0;
}
