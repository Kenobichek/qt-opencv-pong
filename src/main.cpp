#include "game/input/CameraPongGame.h"
#include "builder/GameBuilder.h"

int main(int argc, char *argv[]) {
	auto context = GameBuilder::build(argc, argv);
	CameraPongGame game(std::move(context));
	return game.run();
}