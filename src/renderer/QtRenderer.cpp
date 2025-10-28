#include "QtRenderer.h"

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
		cv::Rect mirrored(paddle.x, paddle.y, paddle.width, paddle.height);
		mirrored.x = frame.width - paddle.x - paddle.width;
		cv::rectangle(mat, mirrored, cv::Scalar(0, 255, 0), 2);
	}

	cv::putText(mat, "Detected paddles: " + std::to_string(state.paddles.size()),
				cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255,255,255), 2);

	const auto& ball = state.ball;
	cv::circle(mat, cv::Point(static_cast<int>(ball.x), static_cast<int>(ball.y)),
				static_cast<int>(ball.radius), cv::Scalar(0, 0, 255), -1);

	cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
	QImage qimg(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
	label_->setPixmap(QPixmap::fromImage(qimg.copy()).scaled(label_->size(), Qt::KeepAspectRatio));
}
