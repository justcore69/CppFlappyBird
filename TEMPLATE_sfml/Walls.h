#pragma once
#include<SFML/Graphics.hpp>

class Walls
{
public:
	sf::RectangleShape roofShape;
	sf::RectangleShape floorShape;

	Walls();
	void update();
	void drawSelf(sf::RenderWindow &_window);
};

