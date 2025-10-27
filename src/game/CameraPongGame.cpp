#include "CameraPongGame.h"

CameraPongGame::CameraPongGame(std::unique_ptr<GameContext> ctx)
	: ctx_(std::move(ctx)) 
{
	ctx_->frameUpdater->setCallback([this]() { processFrame(); });
	ctx_->frameUpdater->start(30);
}

int CameraPongGame::run() { 
	return ctx_->app->exec(); 
}

void CameraPongGame::processFrame() {
	Frame frame;
	if (!ctx_->camera->read(frame)) return;

	auto hands = ctx_->handDetector->detect(frame);
	ctx_->renderer->render(frame, hands);
}
