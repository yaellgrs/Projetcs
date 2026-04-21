#include "game.h"
#include <fstream>

int main()
{
    bool backMenu = false;


    sf::RenderWindow window(sf::VideoMode(800, 600), "Jeu du Pong");    

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
    sf::Text text;
    text.setFont(font);
    text.setPosition(600, 20);
    text.setCharacterSize(75);
    int score = 0;

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

    int g = 0;

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
            x = 0.f;
            y = 0.f;
            if(!backMenu ) g = 2;
        }


        text.setString(std::to_string(score) + " - " + std::to_string(record));
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                    window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                g = 1;
                ball.setPosition(390, 290);
                pong.setPosition(775.f, 200.f);
                ping.setPosition(5.f, 200.f);
                x = SPEED;
                y = SPEED;

                if (score > record)
                {
                    record = score;
                    std::ofstream out("img/record.txt", std::ios::trunc);
                    out << record;
                    out.close();
                    printf("new record : %d\n", record);
                }
                score = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (g == 0)
                {
                    printf("close");
                    window.close();
                }
                else
                    backMenu = true;
            }
            else if(backMenu){
                g = 0;
                backMenu = false;
                Init(ball, ping, pong);
			}   
        }  

        if (g == 0) {
            window.clear();
            window.draw(menu);
            window.display();
        }
        else if (g == 1) {
            int n = ballplay(ball, ping, pong, x, y);
            if ( n > 0 ) {
                score++; 
                if (n == 1) {
                    pingSound.play();
                }
                else {
                    pongSound.play();
                }

 
            }
            player1(ping);
            player2(pong);
            game(window, ping, pong, ball, text);
        }
        else if(g == 2){
            window.clear();
            if(score > record)
                window.draw(Sp_newRecord);
			else
                window.draw(over);
            window.display();
        }
        

    }


    return 0;
}
