#pragma once
#include "GameState.h"
#include "../dto/Rect.h"
#include <vector>

class GameLogic {
	public:
		virtual ~GameLogic() = default;

    virtual void update(GameState& state, const std::vector<Rect>& hands, float dt) = 0;
    virtual void reset(GameState& state) = 0;
};
