#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "Game.h"
#include "Bird.h"
#include "Pillar.h"
#include "Walls.h"

Bird bird = Bird();

std::vector<Pillar> pillars;

Walls walls = Walls();

sf::Text scoreText  = sf::Text();

void drawPillars(sf::RenderWindow &_window);
void updatePillars();
void calculatePillarsCollision(Bird &_bird);
void restart(sf::RenderWindow& _window, Bird& _bird);

int main()
{
    sf::RenderWindow window(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "SlappySquare | by @JustAnCore (github)");
    window.setVerticalSyncEnabled(true);

    for (int i = 0; i < 2; i++) {
        pillars.push_back(Pillar(i * Game::WINDOW_WIDTH/2));
    }

    sf::Font font = sf::Font();

    if (font.loadFromFile("arial.ttf")) {
        scoreText.setString("Score: " + Game::SCORE);
        scoreText.setFont(font);
        scoreText.setCharacterSize(16);
        scoreText.setPosition(3, 3);
    }

    while (window.isOpen())
    { 
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space) {
                    bird.jump();
                }
                if (event.key.code == sf::Keyboard::R) {
                    restart(window, bird);
                }
                break;
            }
        }
        
        bird.update();
        updatePillars();
        calculatePillarsCollision(bird);
        walls.update();
        
        window.clear();

        window.draw(bird);
        drawPillars(window);
        walls.drawSelf(window);
        window.draw(scoreText);

        window.display();

        Game::TIME+=0.1f;
    }

    return 0;
}

void updatePillars() {
    for (int i = 0; i < pillars.size(); i++) {
        pillars[i].update();
    }
}

void drawPillars(sf::RenderWindow &_window) {
    for (int i = 0; i < pillars.size(); i++) {
        _window.draw(pillars[i]);
        _window.draw(pillars[i].secondPillar);
    }
}

void calculatePillarsCollision(Bird &_bird) {
    for (int i = 0; i < pillars.size(); i++) {
        pillars[i].calculateCollision(_bird);
    }
}

void restart(sf::RenderWindow& _window, Bird& _bird) {
    _window.clear();
    _bird.setPosition(_bird.getPosition().x, Game::WINDOW_HEIGHT / 2);

    _bird.isKilled = false;
    Game::GAMEOVER = false;
}