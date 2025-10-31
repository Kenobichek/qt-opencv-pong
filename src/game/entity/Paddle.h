#pragma once
#include "Collider.h"

struct Paddle : Collider {
	float x, y, width, height, speed;

	void update(float dt, bool moveUp, bool moveDown) {
		if (moveUp) y -= speed * dt;
		if (moveDown) y += speed * dt;
	}

	float left() const override { return x; }
	float right() const override { return x + width; }
	float top() const override { return y; }
	float bottom() const override { return y + height; }

	void onCollision(const Collider& other) override {}
	void onCollisionBoundary(float top, float bottom) override {}
};
