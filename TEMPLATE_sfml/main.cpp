#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>

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
void updateScore();
void calculatePillarsCollision(Bird &_bird);
void restart(sf::RenderWindow& _window, Bird& _bird);

int main()
{
    sf::RenderWindow window(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "SlappySquare | by @JustAnCore (github)");
    window.setVerticalSyncEnabled(true);
    sf::Clock restartClock;
    restartClock.restart();

    for (int i = 0; i < 2; i++) {
        pillars.push_back(Pillar(i * Game::WINDOW_WIDTH/2));
    }

    //Set up the UI
    sf::Font font = sf::Font();

    if (font.loadFromFile("arial.ttf")) {
        scoreText.setString("[Score text]");
        scoreText.setFont(font);
        scoreText.setCharacterSize(16);
        scoreText.setPosition(3, 8 + Game::WALLS_SIZE_Y);
    }

    //Load highscore from file
    std::ifstream scoreFile("highscore.ini");
    if (scoreFile.is_open()) {
        std::string line = "default";
        std::getline(scoreFile, line);
        Game::HIGH_SCORE = std::stoi(line);
    }
    else {
        std::cout << "Unable to open highscore.ini | line: 50" << std::endl;
    }

    // GAME LOOP //
    while (window.isOpen())
    { 
        //Debug
        std::cout << "\nGAMEOVER: " + std::to_string((int)Game::GAMEOVER) << std::endl;
        std::cout << "GAME_STARTED: " + std::to_string((int)Game::GAME_STARTED) << std::endl;
        std::cout << "CAN_RESTART: " + std::to_string((int)Game::CAN_RESTART) << std::endl;
        std::cout << "Restart clock: " + std::to_string(restartClock.getElapsedTime().asSeconds()) << std::endl;

        //Event listener
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space) {
                    if (!Game::GAME_STARTED) Game::GAME_STARTED = true;
                    if (Game::CAN_RESTART) restart(window, bird);
                    else bird.jump();
                }
                if (event.key.code == sf::Keyboard::R) {
                    restart(window, bird);
                }
                break;
            }
        }

        if (Game::GAMEOVER) 
        {
            if (restartClock.getElapsedTime().asSeconds() >= 1.5) {
                Game::CAN_RESTART = true;
                restartClock.restart();
            }
        }
        else {
            restartClock.restart();
        }

        //Update
        bird.update();
        updatePillars();
        calculatePillarsCollision(bird);
        walls.update();
        updateScore();
        
        //Draw
        window.clear();

        window.draw(bird);
        drawPillars(window);
        walls.drawSelf(window);
        window.draw(scoreText);

        window.display();
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

void updateScore() {
    std::string _s = "Score: " + std::to_string(Game::SCORE) + "  Highscore: " + std::to_string(Game::HIGH_SCORE);
    scoreText.setString(_s);
}

void restart(sf::RenderWindow& _window, Bird& _bird) {
    _window.clear();
    _bird.setPosition(_bird.getPosition().x, Game::WINDOW_HEIGHT / 2);
    _bird.velocity = 0;

    for (int i = 0; i < pillars.size(); i++) {
        pillars[i].setPosition(pillars[i].startPosition);
    }

    if (Game::SCORE > Game::HIGH_SCORE) {
        Game::HIGH_SCORE = Game::SCORE;
        Game::SCORE = 0;

        std::ofstream scoreFile("highscore.ini");
        if (scoreFile.is_open()) {
            scoreFile << Game::HIGH_SCORE;
            scoreFile.close();
        }
        else {
            std::cout << "Unable to open highscore.ini | line: 130" << std::endl;
        }

    }

    Game::CAN_RESTART = false;
    Game::GAME_STARTED = false;

    _bird.isKilled = false;
    Game::GAMEOVER = false;
}