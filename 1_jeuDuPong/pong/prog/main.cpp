#include "game.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    //players
    sf::RectangleShape ping(sf::Vector2f(20.f, 200.f));
    ping.setPosition(5.f, 200.f);

    //players 2
    sf::RectangleShape pong(sf::Vector2f(20.f, 200.f));
    pong.setPosition(775.f, 200.f);
    pong.setFillColor(sf::Color(255, 0, 232, 255));

    //ball
    sf::CircleShape ball(10.f);
    ball.setPosition(390, 290);

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
        printf("loading error of menu\n");
    }
    sf::Sprite over;
    over.setTexture(overTexture);

    //score
    sf::Font font;
    if(!font.loadFromFile("img/Thanks.ttf")){
        printf("loading error of font\n");
    }
    sf::Text text;
    text.setFont(font);
    text.setPosition(700, 20);
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
    
    sf::Clock clock;
    while (window.isOpen())
    {   
        if (2 > ball.getPosition().x || ball.getPosition().x > 778) {
            x = 0.f;
            y = 0.f;
            g = 2;
        }


        text.setString(std::to_string(score));
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
                score = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
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
            window.draw(over);
            window.display();
        }
        

    }

    return 0;
}