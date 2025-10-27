#include "Camera.h"
#include <opencv2/opencv.hpp>

class OpenCVCamera : public Camera {
	public:
		bool open(int index) override;
		bool read(Frame &frame) override;
		void release() override;

	private:
		cv::VideoCapture cap_;
};
