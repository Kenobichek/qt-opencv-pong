#include "game/CameraPongGame.h"
#include "game/GameBuilder.h"

int main(int argc, char *argv[]) {
	auto context = GameBuilder::build(argc, argv);
	CameraPongGame game(std::move(context));
	return game.run();
}