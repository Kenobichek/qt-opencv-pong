#pragma once
#include <vector>
#include "../dto/Frame.h"

class Camera {
	public:
		virtual ~Camera() = default;
		virtual bool open(int index) = 0;
		virtual bool read(Frame &frame) = 0;
		virtual void release() = 0;
};
