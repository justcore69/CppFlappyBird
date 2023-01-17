#include "Walls.h"
#include "Game.h"

#include<SFML/Graphics.hpp>

Walls::Walls() {
	roofShape.setSize(sf::Vector2f(Game::WINDOW_WIDTH, Game::WALLS_SIZE_Y));
	floorShape.setSize(roofShape.getSize());

	roofShape.setPosition(0,0);
	floorShape.setPosition(0, Game::WINDOW_HEIGHT - floorShape.getSize().y);
}

void Walls::update() {
	//Graphics
	roofShape.setFillColor(sf::Color::Black);
	roofShape.setOutlineThickness(2);
	roofShape.setOutlineColor(sf::Color::White);

	floorShape.setFillColor(sf::Color::Black);
	floorShape.setOutlineThickness(2);
	floorShape.setOutlineColor(sf::Color::White);
}

void Walls::drawSelf(sf::RenderWindow &_window) {
	_window.draw(roofShape);
	_window.draw(floorShape);
}