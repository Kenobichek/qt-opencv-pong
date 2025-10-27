#include "OpenCVCamera.h"

bool OpenCVCamera::open(int index) {
	return cap_.open(index);
}

bool OpenCVCamera::read(Frame &frame) {
	cv::Mat mat;
	cap_ >> mat;
	if (mat.empty()) return false;

	frame.width = mat.cols;
	frame.height = mat.rows;
	frame.data.assign(mat.data, mat.data + mat.total() * mat.channels());
	return true;
}

void OpenCVCamera::release() {
	cap_.release();
}
