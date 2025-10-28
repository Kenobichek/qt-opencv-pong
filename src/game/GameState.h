#pragma once
#include <vector>
#include "../dto/Screen.h"

struct Paddle {
	float x, y;
	float width, height;
};

struct Ball {
	float x = 0;
	float y = 0;
	float vx = 0;
	float vy = 0;
	float radius = 10;
};

struct GameState {
	Screen screen;
	std::vector<Paddle> paddles;
	Ball ball;
	std::vector<int> scores;
};
