#pragma once
#include<SFML/Graphics.hpp>

#include "Bird.h"

class Pillar : public sf::RectangleShape
{
public:
	sf::RectangleShape secondPillar;
	float secondPillarOffset;

	void update();
	void toRight();
	void calculateCollision(Bird &_bird);
	Pillar(float _offsetX);
};

