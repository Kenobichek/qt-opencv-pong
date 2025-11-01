#include "DefaultGameLogic.h"

void DefaultGameLogic::update(
	GameState& state, 
	const std::vector<Rect>& hands, 
	float dt
) {
	movementSystem_.update(state.balls, dt);
	cameraInputSystem_.update(state.paddles, hands);
	
	std::vector<Entity*> all;
	for (auto& ball : state.balls) all.push_back(&ball);
	for (auto& paddle : state.paddles) all.push_back(&paddle);

	collisionSystem_.checkCollisions(all, dt);

	for (auto& ball : state.balls) {
		collisionSystem_.checkBoundaries(ball, 0.0f, state.screen.height());
	}
}

void DefaultGameLogic::reset(GameState& state) {
	state.scores = {0, 0};
}
