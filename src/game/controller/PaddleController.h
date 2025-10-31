#pragma once
#include "../state/GameState.h"
#include "../../dto/Rect.h"
#include <vector>

class PaddleController {
	public:
		void update(GameState& state, const std::vector<Rect>& hands) {
			state.paddles.resize(hands.size());
			for (std::size_t i = 0; i < hands.size(); ++i) {
				state.paddles[i].x = hands[i].x;
				state.paddles[i].y = hands[i].y;
				state.paddles[i].width = hands[i].width;
				state.paddles[i].height = hands[i].height;
			}
		}
};
