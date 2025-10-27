#include "OpenCVHandDetector.h"
#include <opencv2/opencv.hpp>

std::vector<Rect> OpenCVHandDetector::detect(const Frame& frame) {
	std::vector<Rect> hands;
	if (frame.data.empty() || frame.width <= 0 || frame.height <= 0)
		return hands;

	
	cv::Mat mat(frame.height, frame.width, CV_8UC3, const_cast<unsigned char*>(frame.data.data()));
		
	cv::Mat ycrcb, mask;
	cv::cvtColor(mat, ycrcb, cv::COLOR_BGR2YCrCb);
	cv::inRange(ycrcb, cv::Scalar(0,133,77), cv::Scalar(255,173,127), mask);

	cv::morphologyEx(mask, mask, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1,-1), 2);
	cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1,-1), 2);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	int width = mat.cols;
	for (auto& c : contours) {
		double area = cv::contourArea(c);
		if (area < 5000) continue;

		cv::Rect box = cv::boundingRect(c);
		float cx = box.x + box.width / 2.0f;
		float ratio = (float)box.height / box.width;

		bool left = cx < width * 0.25;
		bool right = cx > width * 0.75;
		if (!left && !right) continue;
		if (ratio < 1.0 || ratio > 4.0) continue;
		if (box.width < 40 || box.height < 60) continue;

		hands.push_back({ box.x, box.y, box.width, box.height });
	}

	if (hands.size() > 2) {
		std::sort(hands.begin(), hands.end(), [](const Rect& a, const Rect& b) {
			return a.width * a.height > b.width * b.height;
		});
		hands.resize(2);
	}

	return hands;
}
