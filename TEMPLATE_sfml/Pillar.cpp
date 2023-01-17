#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <vector>
#include <iostream>

#include "Pillar.h"
#include "Game.h"

Pillar::Pillar(float _offsetX) {
	setSize(sf::Vector2f(32, 512));

	srand(time(nullptr));
	float _offsetY = (rand() % 129 * 1.5f) - 64 * 1.5f;
	//float _offsetY = 0;

	secondPillar = sf::RectangleShape();
	secondPillarOffset = 128;
	scored = false;

	setPosition(sf::Vector2f(Game::WINDOW_WIDTH + _offsetX, (Game::WINDOW_HEIGHT / 2) + _offsetY - secondPillarOffset/2));
	startPosition = getPosition();

	setOrigin(getSize().x/2, getSize().y);
	secondPillar.setOrigin(getSize().x/2, 0);
	secondPillar.setSize(getSize());
}

void Pillar::update() {

	//graphics
	setFillColor(sf::Color::Black);
	setOutlineThickness(2);
	setOutlineColor(sf::Color::White);

	//move
	if(!Game::GAMEOVER)setPosition(sf::Vector2f(getPosition().x - Game::SCREEN_SPEED, getPosition().y));
	if (getPosition().x <= 0) toRight();

	//second pillar
	secondPillar.setPosition(getPosition().x, getPosition().y + secondPillarOffset);
	secondPillar.setFillColor(getFillColor());
	secondPillar.setOutlineThickness(getOutlineThickness());
	secondPillar.setOutlineColor(getOutlineColor());
}

void Pillar::toRight() {
	srand(time(nullptr));
	float _offsetY = (rand() % 129 * 1.5f) - 64 * 1.5f;
	//float _offsetY = 0;

	setPosition(sf::Vector2f(Game::WINDOW_WIDTH, (Game::WINDOW_HEIGHT / 2) + _offsetY));

	scored = false;
}

void Pillar::calculateCollision(Bird &_bird) {
	sf::Vector2f _bp = _bird.getPosition();
	sf::Vector2f _borig = _bird.getOrigin();

	std::vector<sf::Vector2f> _bdots =
	{
		sf::Vector2f(_bp.x - _borig.x, _bp.y - _borig.y),
		sf::Vector2f(_bp.x + _borig.x, _bp.y - _borig.y),
		sf::Vector2f(_bp.x - _borig.x, _bp.y + _borig.y),
		sf::Vector2f(_bp.x + _borig.x, _bp.y + _borig.y),
	};

	//Check collision with the top pillar
	sf::Vector2f _porig = getOrigin();
	sf::Vector2f _pp = getPosition();

	for (int i = 0; i < _bdots.size(); i++) {
		if (_bdots[i].x >= _pp.x - _porig.x && _bdots[i].x <= _pp.x + getSize().x - _porig.x) {
			if (_bdots[i].y >= _pp.y - _porig.y && _bdots[i].y <= _pp.y + getSize().y - _porig.y) {
				_bird.kill();
			}
		}
	}

	//Check collision with the bottom pillar
	sf::Vector2f _sorig = secondPillar.getOrigin();
	sf::Vector2f _sp = secondPillar.getPosition();

	for (int i = 0; i < _bdots.size(); i++) {
		if (_bdots[i].x >= _sp.x - _sorig.x && _bdots[i].x <= _sp.x + getSize().x - _sorig.x) {
			if (_bdots[i].y >= _sp.y - _sorig.y && _bdots[i].y <= _sp.y + getSize().y - _sorig.y) {
				_bird.kill();
			}
		}
	}

	//Add score if pillar was passed by player
	std::cout << std::to_string(roundf(getPosition().x)) + " " + std::to_string(roundf(_bird.getPosition().x)) << std::endl;
	if (getPosition().x <= roundf(_bird.getPosition().x) && !scored) {
		Game::SCORE++;
		if(Game::SCORE > Game::HIGH_SCORE) Game::HIGH_SCORE = Game::SCORE;
		scored = true;
	}
}
