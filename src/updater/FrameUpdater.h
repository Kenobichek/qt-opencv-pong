#pragma once
#include <functional>

class FrameUpdater {
	public:
		virtual ~FrameUpdater() = default;

		virtual void setCallback(std::function<void()> callback) = 0;

		virtual void start(int intervalMs) = 0;
		virtual void stop() = 0;
};
