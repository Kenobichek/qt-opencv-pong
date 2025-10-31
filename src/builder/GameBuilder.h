#pragma once
#include "GameContext.h"

class GameBuilder {
	public:
		static std::unique_ptr<GameContext> build(int &argc, char **argv);
};
