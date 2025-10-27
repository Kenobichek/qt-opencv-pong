#pragma once
#include "GameContext.h"

class CameraPongGame {
	public:
		explicit CameraPongGame(std::unique_ptr<GameContext> ctx);

		int run();

	private:
		void processFrame();

		std::unique_ptr<GameContext> ctx_;
};
