#pragma once
#include "Renderer.h"
#include <QLabel>
#include <opencv2/opencv.hpp>

class QtRenderer : public Renderer {
	public:
		QtRenderer();
		~QtRenderer();
		
		void render(const Frame& frame, const GameState& state) override;

	private:
		QLabel* label_;
};
