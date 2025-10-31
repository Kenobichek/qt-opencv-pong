#include "DefaultGameLogic.h"

void DefaultGameLogic::update(
	GameState& state, 
	const std::vector<Rect>& hands, 
	float dt
) {

	paddleController.update(state, hands);
	ballController.update(state, dt);
	
	std::vector<Collider*> colliders;
	for (auto& ball : state.balls) colliders.push_back(&ball);
	for (auto& paddle : state.paddles) colliders.push_back(&paddle);

	collisionSystem.checkObjectCollisions(colliders);

	collisionSystem.checkBoundaryCollisions(colliders, 0.0f, state.screen.height());
}

void DefaultGameLogic::reset(GameState& state) {
	state.scores = {0, 0};
	state.paddles.clear();
	state.balls.clear();
}
