#pragma once
#include "Collider.h"

struct Ball : Collider {
	float x, y, dx, dy, radius;

	void update(float dt) {
		x += dx * dt;
		y += dy * dt;
	}

	float left() const override { return x - radius; }
	float right() const override { return x + radius; }
	float top() const override { return y - radius; }
	float bottom() const override { return y + radius; }

	void onCollision(const Collider& other) override {
		dx = -dx;
	}

	void onCollisionBoundary(float top, float bottom) override {
		dy = -dy;
	}
};
