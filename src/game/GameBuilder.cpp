#include "GameBuilder.h"
#include "../app/QtApp.h"
#include "../camera/OpenCVCamera.h"
#include "../detector/OpenCVHandDetector.h"
#include "../renderer/QtRenderer.h"
#include "../updater/QtFrameUpdater.h"
#include "../game/DefaultGameLogic.h"

std::unique_ptr<GameContext> GameBuilder::build(int &argc, char **argv) {
	auto ctx = std::make_unique<GameContext>();

	ctx->app = std::make_unique<QtApp>(argc, argv);
	ctx->camera = std::make_unique<OpenCVCamera>();
	ctx->handDetector = std::make_unique<OpenCVHandDetector>();
	ctx->renderer = std::make_unique<QtRenderer>();
	ctx->frameUpdater = std::make_unique<QtFrameUpdater>();
	ctx->gameLogic = std::make_unique<DefaultGameLogic>();

	int camIndex = (argc > 1) ? std::stoi(argv[1]) : 0;
	ctx->camera->open(camIndex);

	return ctx;
}
