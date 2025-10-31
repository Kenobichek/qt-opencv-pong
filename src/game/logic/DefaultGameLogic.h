#pragma once
#include "GameLogic.h"
#include "../controller/PaddleController.h"
#include "../controller/BallController.h"
#include "../system/Collision.h"

class DefaultGameLogic : public GameLogic {
	public:
		void update(GameState& state, const std::vector<Rect>& hands, float dt) override;
		void reset(GameState& state) override;

	private:
		PaddleController paddleController;
		BallController ballController;
		CollisionSystem collisionSystem;
};
