#pragma once
#include "Renderer.h"
#include <QLabel>
#include <opencv2/opencv.hpp>

class QtRenderer : public Renderer {
	public:
		QtRenderer();
		~QtRenderer();
		
		void render(const Frame& frame, const std::vector<Rect>& hands) override;

	private:
		QLabel* label_;
};
