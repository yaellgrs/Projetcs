#include "game.h"



int ballplay(sf::CircleShape& ball, sf::RectangleShape ping, sf::RectangleShape& pong, float& x, float& y) {

    sf::FloatRect ballBox = ball.getGlobalBounds();
    if (ballBox.intersects(ping.getGlobalBounds())) {
        x = -x;
        ball.move(x, y);
        x += 0.5;
        ball.setFillColor(sf::Color(255, 255, 255, 255));
        return 1;

    }
    if (ballBox.intersects(pong.getGlobalBounds())) {
        x += 0.5;
        x = -x;
        ball.move(x, y);
        ball.setFillColor(sf::Color(255, 0, 232, 255));
        return 2;

    }
    else if ((0 < ball.getPosition().y && ball.getPosition().y < 580) && (0 < ball.getPosition().x && ball.getPosition().x < 780)) {
        ball.move(x, y);
    }
    else if (0 >= ball.getPosition().y || ball.getPosition().y >= 580) {
        y = -y;
        ball.move(x, y);
    }
    else if (0 >= ball.getPosition().x || ball.getPosition().x >= 780) {
        x = -x;
        ball.move(x, y);
    }
    return 0;
}

void player1(sf::RectangleShape& ping) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (ping.getPosition().y < 400)) {
        ping.move(0.f, 5.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (ping.getPosition().y > 0)) {
        ping.move(0.f, -5.f);
    }
}

void player2(sf::RectangleShape& pong) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (pong.getPosition().y < 400)) {
        pong.move(0.f, 5.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (pong.getPosition().y > 0)) {
        pong.move(0.f, -5.f);
    }
}

void game(sf::RenderWindow& window, sf::RectangleShape& ping, sf::RectangleShape& pong,  sf::CircleShape& ball, sf::Text text, sf::Text speed, sf::Text Txt_timerStart,sf::Text Txt_inputPlayer1, sf::Text Txt_inputPlayer2) {
    window.clear();
    window.draw(ping);
    window.draw(pong);
    window.draw(ball);
    window.draw(text);
    window.draw(speed);
    window.draw(Txt_timerStart);
    window.draw(Txt_inputPlayer1);
    window.draw(Txt_inputPlayer2);
    window.display();
}


void Init(sf::CircleShape& ball, sf::RectangleShape& ping, sf::RectangleShape& pong)
{
    ball.setPosition(390, 290);
    pong.setPosition(775.f, 200.f);
    ping.setPosition(5.f, 200.f);
}

void InitSpeed(float& x, float& y) {
     x = (rand() % 2 == 0) ? -SPEED: SPEED;
     y = (rand() % 2 == 0) ? -SPEED: SPEED;
}