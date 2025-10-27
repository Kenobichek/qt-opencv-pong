#pragma once
#include <memory>
#include "../app/App.h"
#include "../camera/Camera.h"
#include "../detector/HandDetector.h"
#include "../renderer/Renderer.h"
#include "../updater/FrameUpdater.h"

struct GameContext {
	std::unique_ptr<App> app;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<HandDetector> handDetector;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<FrameUpdater> frameUpdater;
};
