#pragma once
#include "../entity/Entity.h"
#include "../../dto/Rect.h"
#include <vector>

class CameraInputSystem {
	public:
		void update(std::vector<Entity>& paddles, const std::vector<Rect>& hands);
};
