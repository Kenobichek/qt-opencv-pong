#pragma once
#include "../entity/Collider.h"
#include <vector>

class CollisionSystem {
	public:
		void checkObjectCollisions(std::vector<Collider*>& colliders);
		void checkBoundaryCollisions(const std::vector<Collider*>& colliders, float top, float bottom);

	private:
		bool isColliding(const Collider& a, const Collider& b);
};
