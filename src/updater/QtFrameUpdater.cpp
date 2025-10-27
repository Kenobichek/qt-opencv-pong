#include "QtFrameUpdater.h"

QtFrameUpdater::QtFrameUpdater(QObject* parent) {
	timer_ = new QTimer(parent);
}

QtFrameUpdater::~QtFrameUpdater() {
	timer_->stop();
	delete timer_;
}

void QtFrameUpdater::setCallback(std::function<void()> callback) {
	callback_ = callback;
	QObject::connect(timer_, &QTimer::timeout, [this]() {
		if (callback_) callback_();
	});
}

void QtFrameUpdater::start(int intervalMs) {
	timer_->start(intervalMs);
}

void QtFrameUpdater::stop() {
	timer_->stop();
}
