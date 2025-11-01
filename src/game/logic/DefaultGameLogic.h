#pragma once
#include "GameLogic.h"
#include "../system/Collision.h"
#include "../system/Movement.h"
#include "../system/CameraInput.h"

class DefaultGameLogic : public GameLogic {
	public:
		void update(GameState& state, const std::vector<Rect>& hands, float dt) override;
		void reset(GameState& state) override;

	private:
		CollisionSystem collisionSystem_;
		MovementSystem movementSystem_;
		CameraInputSystem cameraInputSystem_;
};
