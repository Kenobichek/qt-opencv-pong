#pragma once
#include "GameLogic.h"

class DefaultGameLogic : public GameLogic {
	public:
		void update(GameState& state, const std::vector<Rect>& hands, float dt) override;
		void reset(GameState& state) override;

	private:
		void updatePaddles(GameState& state, const std::vector<Rect>& hands);
		void updateBall(GameState& state, const float dt);
		void checkCollisions(GameState& state);
};
