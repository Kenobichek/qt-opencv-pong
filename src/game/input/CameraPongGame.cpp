#include "CameraPongGame.h"
#include <iostream>

CameraPongGame::CameraPongGame(std::unique_ptr<GameContext> ctx)
	: ctx_(std::move(ctx)) 
{
	ctx_->gameLogic->reset(ctx_->state);
	ctx_->frameUpdater->setCallback([this]() { processFrame(); });
	ctx_->frameUpdater->start(30);
}

int CameraPongGame::run() {
	std::cout << "Running..." << std::endl;
	return ctx_->app->exec(); 
}

void CameraPongGame::processFrame() {
	Frame frame;
	if (!ctx_->camera->read(frame)) return;

	auto hands = ctx_->handDetector->detect(frame);
	auto& state	 = ctx_->state;

	ctx_->gameLogic->update(state, hands, 0.016f);
	ctx_->renderer->render(frame, state);
}
