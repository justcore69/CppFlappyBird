#include "Pillar.h"
#include "Game.h"

Pillar::Pillar(float _offset) {
	setSize(sf::Vector2f(16, 32));
	setPosition(sf::Vector2f(Game::WINDOW_WIDTH + _offset, Game::WINDOW_HEIGHT / 2));
	setOrigin(8, 16);
}

void Pillar::update() {

	//graphics
	setFillColor(sf::Color::Black);
	setOutlineThickness(2);
	setOutlineColor(sf::Color::White);

	//move
	setPosition(sf::Vector2f(getPosition().x - Game::SCREEN_SPEED, getPosition().y));
	if (getPosition().x <= 0) toRight();
}

void Pillar::toRight() {
	setPosition(sf::Vector2f(Game::WINDOW_WIDTH, getPosition().y));
}
