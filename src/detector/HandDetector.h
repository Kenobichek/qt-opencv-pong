#pragma once
#include <vector>
#include "../dto/Frame.h"
#include "../dto/Rect.h"

class HandDetector {
	public:
		virtual ~HandDetector() = default;
		virtual std::vector<Rect> detect(const Frame& frame) = 0;
};
