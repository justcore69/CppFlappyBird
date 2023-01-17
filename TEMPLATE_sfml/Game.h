#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;

	static float SCREEN_SPEED;

	static int WALLS_SIZE_Y;

	static float TIME;

	static int SCORE;
	static int HIGH_SCORE;

	static bool GAMEOVER;

	Game();
};

