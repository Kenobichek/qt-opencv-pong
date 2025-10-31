#pragma once
#include "../state/GameState.h"

class BallController {
public:
	void update(GameState& state, float dt) {
		for (auto& ball : state.balls) {
			ball.x += ball.dx * dt;
			ball.y += ball.dy * dt;
		}
	}
};
