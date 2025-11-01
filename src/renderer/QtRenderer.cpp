#include "QtRenderer.h"
#include "../game/component/Position.h"
#include "../game/component/Collider.h"
#include "../game/entity/Entity.h"

QtRenderer::QtRenderer() {
	label_ = new QLabel();
	label_->setWindowTitle("Camera Pong");
	label_->resize(640, 480);
	label_->show();
}

QtRenderer::~QtRenderer() {
	delete label_;
}

void QtRenderer::render(const Frame& frame, const GameState& state) {
	if (frame.data.empty()) return;

	cv::Mat mat(frame.height, frame.width, CV_8UC3, const_cast<unsigned char*>(frame.data.data()));
	mat = mat.clone();

	cv::flip(mat, mat, 1);

	for (const auto& paddle : state.paddles) {
		auto pos = paddle.getComponent<PositionComponent>();
		auto col = paddle.getComponent<ColliderComponent>();
		if (!pos || !col) continue;

		int drawX = frame.width - static_cast<int>(pos->x) - static_cast<int>(col->width);
		int drawY = static_cast<int>(pos->y);

		cv::rectangle(mat, cv::Rect(drawX, drawY, static_cast<int>(col->width), static_cast<int>(col->height)),
					cv::Scalar(0, 255, 0), 2);
	}

	cv::putText(
		mat,
		"Detected paddles: " + std::to_string(state.paddles.size()),
		cv::Point(10, 30),
		cv::FONT_HERSHEY_SIMPLEX,
		0.8,
		cv::Scalar(255, 255, 255),
		2
	);

	for (const auto& ball : state.balls) {
		auto pos = ball.getComponent<PositionComponent>();
		auto col = ball.getComponent<ColliderComponent>();
		if (!pos || !col) continue;

		int cx = static_cast<int>(pos->x + col->width / 2.f);
		int cy = static_cast<int>(pos->y + col->height / 2.f);
		int radius = static_cast<int>(std::min(col->width, col->height) / 2.f);

		int drawCx = frame.width - cx;
		cv::circle(mat, cv::Point(drawCx, cy), radius, cv::Scalar(0, 0, 255), -1);
	}

	cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
	QImage qimg(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
	label_->setPixmap(QPixmap::fromImage(qimg.copy()).scaled(label_->size(), Qt::KeepAspectRatio));
}
