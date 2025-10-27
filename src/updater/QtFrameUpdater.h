#pragma once
#include "FrameUpdater.h"
#include <QTimer>
#include <functional>
#include <QObject>

class QtFrameUpdater : public FrameUpdater {
	public:
		explicit QtFrameUpdater(QObject* parent = nullptr);
		~QtFrameUpdater() override;

		void setCallback(std::function<void()> callback) override;
		void start(int intervalMs) override;
		void stop() override;

	private:
		QTimer* timer_;
		std::function<void()> callback_;
};
