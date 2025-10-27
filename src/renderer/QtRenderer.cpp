#include "QtRenderer.h"

void QtRenderer::render(const Frame& frame, const std::vector<Rect>& hands) {
	if (frame.data.empty()) return;

	cv::Mat mat(frame.height, frame.width, CV_8UC3, const_cast<unsigned char*>(frame.data.data()));

	cv::flip(mat, mat, 1);

	for (const auto& h : hands) {
		cv::Rect mirrored(h.x, h.y, h.width, h.height);
		mirrored.x = frame.width - h.x - h.width;
		cv::rectangle(mat, mirrored, cv::Scalar(0, 255, 0), 2);
	}

	cv::putText(mat, "Detected hands: " + std::to_string(hands.size()),
				cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255,255,255), 2);

	cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
	QImage qimg(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
	label_->setPixmap(QPixmap::fromImage(qimg).scaled(label_->size(), Qt::KeepAspectRatio));
}
