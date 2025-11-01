#pragma once
#include "Component.h"

struct ColliderComponent : Component {
	float width = 0;
	float height = 0;

	ColliderComponent(float w = 0, float h = 0) : width(w), height(h) {}
};
