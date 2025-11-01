#pragma once
#include "Component.h"

struct VelocityComponent : Component {
	float vx = 0;
	float vy = 0;

	VelocityComponent(float vx_ = 0, float vy_ = 0) : vx(vx_), vy(vy_) {}
};
