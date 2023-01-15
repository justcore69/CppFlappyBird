#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <vector>

#include "Pillar.h"
#include "Game.h"

Pillar::Pillar(float _offsetX) {
	setSize(sf::Vector2f(32, 512));

	srand(time(nullptr));
	float _offsetY = (rand() % 129*2) - 64*2;
	//float _offsetY = 0;

	secondPillar = sf::RectangleShape();
	secondPillarOffset = 128;

	setPosition(sf::Vector2f(Game::WINDOW_WIDTH + _offsetX, (Game::WINDOW_HEIGHT / 2) + _offsetY - secondPillarOffset/2));

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
	float _offsetY = (rand() % 129*2) - 64*2;
	//float _offsetY = 0;

	setPosition(sf::Vector2f(Game::WINDOW_WIDTH, (Game::WINDOW_HEIGHT / 2) + _offsetY));
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

	sf::Vector2f _porig = getOrigin();
	sf::Vector2f _pp = getPosition();

	//Check collision with the top pillar
	for (int i = 0; i < _bdots.size(); i++) {
		if (_bdots[i].x >= _pp.x - _porig.x && _bdots[i].x <= _pp.x + getSize().x - _porig.x) {
			if (_bdots[i].y >= _pp.y - _porig.y && _bdots[i].y <= _pp.y + getSize().y - _porig.y) {
				_bird.kill();
			}
		}
	}

	sf::Vector2f _sorig = secondPillar.getOrigin();
	sf::Vector2f _sp = secondPillar.getPosition();

	//Check collision with the bottom pillar
	for (int i = 0; i < _bdots.size(); i++) {
		if (_bdots[i].x >= _sp.x - _sorig.x && _bdots[i].x <= _sp.x + getSize().x - _sorig.x) {
			if (_bdots[i].y >= _sp.y - _sorig.y && _bdots[i].y <= _sp.y + getSize().y - _sorig.y) {
				_bird.kill();
			}
		}
	}
}
