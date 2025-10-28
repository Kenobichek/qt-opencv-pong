#pragma once
#include "../detector/HandDetector.h"
#include "../dto/Frame.h"
#include "../game/GameState.h"

class Renderer {
	public:
		virtual ~Renderer() = default;

		virtual void render(const Frame& frame, const GameState& state) = 0;
};
