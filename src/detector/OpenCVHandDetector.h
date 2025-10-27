#pragma once
#include "HandDetector.h"

class OpenCVHandDetector : public HandDetector {
	public:
		std::vector<Rect> detect(const Frame& frame) override;
};
