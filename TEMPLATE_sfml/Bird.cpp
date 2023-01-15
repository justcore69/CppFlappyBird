#include "Bird.h"

Bird::Bird() {
    setSize(sf::Vector2f(16, 16));
    setPosition(sf::Vector2f(Game::WINDOW_WIDTH / 4, Game::WINDOW_HEIGHT / 2));
    setOrigin(8, 8);
}

void Bird::update() {

    //graphics
    setFillColor(sf::Color::Black);
    setOutlineThickness(2);
    if (isKilled) {
        setOutlineColor(sf::Color::Red);
    }
    else {
        
        setOutlineColor(sf::Color::White);
    }

    //gravity
    if (velocity > 0) velocity += 0.15f;
    else velocity += 0.08f;

    //move
    if (getPosition().y < Game::WINDOW_HEIGHT - 16 && getPosition().y > 16) {
        setPosition(sf::Vector2f(getPosition().x, getPosition().y + velocity));
    }
    else if (getPosition().y >= Game::WINDOW_HEIGHT - 16) {
        velocity = 0;
    }
    else if (getPosition().y <= 16) {
        velocity = std::fmax(velocity, 0.0);
        setPosition(sf::Vector2f(getPosition().x, getPosition().y + velocity));
    }

    //check collision
    if (getPosition().y <= 16 || getPosition().y >= Game::WINDOW_HEIGHT - 16) { //with floor and roof
        if(!isKilled) kill();
    }
}

void Bird::jump() {

    if (isKilled) return;

    if (velocity > 0) velocity = 0;
    velocity += -4;
    if (velocity < -6) velocity = -6;
}

void Bird::kill() {
    isKilled = true;
}