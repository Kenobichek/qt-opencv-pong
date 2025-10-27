#pragma once
#include "Renderer.h"
#include <QLabel>
#include <opencv2/opencv.hpp>

class QtRenderer : public Renderer {
	public:
		explicit QtRenderer(QLabel* label) : label_(label) {}
		void render(const Frame& frame, const std::vector<Rect>& hands) override;

	private:
		QLabel* label_;
};
