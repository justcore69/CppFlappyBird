#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "Game.h"
#include "Bird.h"
#include "Pillar.h"

Bird bird = Bird();

std::vector<Pillar> pillars;

sf::Text scoreText  = sf::Text();

void drawPillars(sf::RenderWindow &_window);
void updatePillars();

int main()
{
    sf::RenderWindow window(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "SFML works!");
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
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code = sf::Keyboard::Space) {
                    bird.jump();
                }
            }

            if (event.type == sf::Event::Closed) { window.close(); }
        }
        
        bird.update();
        updatePillars();
        
        window.clear();

        window.draw(bird);
        drawPillars(window);
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
    }
}