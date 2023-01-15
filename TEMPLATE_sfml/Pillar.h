#pragma once
#include<SFML/Graphics.hpp>

class Pillar : public sf::RectangleShape
{
public:
	void update();
	void toRight();
	Pillar(float _offset);
};

