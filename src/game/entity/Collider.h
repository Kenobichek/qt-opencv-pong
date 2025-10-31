#pragma once

class Collider {
	public:
		virtual ~Collider() = default;
		virtual float left() const = 0;
		virtual float right() const = 0;
		virtual float top() const = 0;
		virtual float bottom() const = 0;
		virtual void onCollision(const Collider& other) = 0;
		virtual void onCollisionBoundary(float top, float bottom) = 0;
};
