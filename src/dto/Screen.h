#pragma once

struct Screen {
	public:
		Screen(int w = 640, int h = 480) : width_(w), height_(h) {}

		int width() const { return width_; }
		int height() const { return height_; }

		void setWidth(int w) { width_ = w; }
		void setHeight(int h) { height_ = h; }
		void setSize(int w, int h) { width_ = w; height_ = h; }

	private:
		int width_;
		int height_;
};
