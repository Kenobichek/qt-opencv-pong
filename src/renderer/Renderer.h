#pragma once
#include "../detector/HandDetector.h"
#include "../dto/Frame.h"

class Renderer {
	public:
		virtual ~Renderer() = default;

		virtual void render(const Frame& frame, const std::vector<Rect>& hands) = 0;
};
