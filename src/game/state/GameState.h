#pragma once
#include <vector>
#include "../../dto/Screen.h"
#include "../entity/Paddle.h"
#include "../entity/Ball.h"

struct GameState {
	Screen screen;
	std::vector<Paddle> paddles;
	std::vector<Ball> balls;
	std::vector<int> scores;
};
