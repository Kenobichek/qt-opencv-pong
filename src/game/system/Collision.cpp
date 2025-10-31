#include "Collision.h"

void CollisionSystem::checkObjectCollisions(std::vector<Collider*>& colliders) {
	for (std::size_t i = 0; i < colliders.size(); ++i) {
		for (std::size_t j = i + 1; j < colliders.size(); ++j) {
			if (isColliding(*colliders[i], *colliders[j])) {
				colliders[i]->onCollision(*colliders[j]);
				colliders[j]->onCollision(*colliders[i]);
			}
		}
	}
}

void CollisionSystem::checkBoundaryCollisions(const std::vector<Collider*>& colliders, float top, float bottom) {
	for (auto* collider : colliders) {
		if (collider->top() < top || collider->bottom() > bottom) {
			collider->onCollisionBoundary(top, bottom);
		}
	}
}

bool CollisionSystem::isColliding(const Collider& a, const Collider& b) {
	return !(a.right() < b.left() || a.left() > b.right() ||
			a.bottom() < b.top() || a.top() > b.bottom());
}