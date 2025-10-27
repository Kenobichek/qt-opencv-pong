#pragma once
#include <vector>

struct Frame {
	int width;
	int height;
	std::vector<unsigned char> data;
};