#pragma once
#include<SFML/Graphics.hpp>

#include "Game.h"

class Bird : public sf::RectangleShape {
public:

    float velocity = 0;
    bool isKilled = false;

    Bird();
    void update();
    void jump();
    void kill();
};

