#include "Collision.h"
#include "../component/Collider.h"
#include "../component/Position.h"
#include "../component/Velocity.h"

void CollisionSystem::checkBoundaries(Entity& obj, float top, float bottom) {
	auto pos = obj.getComponent<PositionComponent>();
	auto col = obj.getComponent<ColliderComponent>();
	auto vel = obj.getComponent<VelocityComponent>();
	if (!pos || !col || !vel) return;

	if (pos->y < top) {
		pos->y = top;
		vel->vy = -vel->vy;
	} else if (pos->y + col->height > bottom) {
		pos->y = bottom - col->height;
		vel->vy = -vel->vy;
	}
}

void CollisionSystem::checkCollisions(std::vector<Entity*>& objects, float dt) {
	const size_t n = objects.size();
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = i + 1; j < n; ++j) {
			handleCollision(*objects[i], *objects[j], dt);
		}
	}
}

void CollisionSystem::handleCollision(Entity& a, Entity& b, float dt) {
	auto aPos = a.getComponent<PositionComponent>();
	auto aVel = a.getComponent<VelocityComponent>();
	auto aDim = a.getComponent<ColliderComponent>();

	auto bPos = b.getComponent<PositionComponent>();
	auto bVel = b.getComponent<VelocityComponent>();
	auto bDim = b.getComponent<ColliderComponent>();

	if (!aPos || !aDim || !bPos || !bDim) return;
	if (aDim->width <= 0 || aDim->height <= 0 || bDim->width <= 0 || bDim->height <= 0) return;

	float nextAX = aPos->x + (aVel ? aVel->vx * dt : 0.f);
	float nextAY = aPos->y + (aVel ? aVel->vy * dt : 0.f);
	float nextBX = bPos->x + (bVel ? bVel->vx * dt : 0.f);
	float nextBY = bPos->y + (bVel ? bVel->vy * dt : 0.f);

	bool overlapX = nextAX < nextBX + bDim->width && nextAX + aDim->width > nextBX;
	bool overlapY = nextAY < nextBY + bDim->height && nextAY + aDim->height > nextBY;

	if (!overlapX || !overlapY) return;

	float overlapLeft   = (nextAX + aDim->width) - nextBX;
	float overlapRight  = (nextBX + bDim->width) - nextAX;
	float overlapTop    = (nextAY + aDim->height) - nextBY;
	float overlapBottom = (nextBY + bDim->height) - nextAY;

	float minOverlapX = std::min(overlapLeft, overlapRight);
	float minOverlapY = std::min(overlapTop, overlapBottom);

	if (minOverlapX < minOverlapY) {
		float signA = (aVel && aVel->vx != 0.f) ? (aVel->vx > 0.f ? 1.f : -1.f) : 1.f;
		float signB = (bVel && bVel->vx != 0.f) ? (bVel->vx > 0.f ? 1.f : -1.f) : 1.f;

		if (aVel) aPos->x -= minOverlapX * signA;
		if (bVel) bPos->x += minOverlapX * signB;

		if (aVel) aVel->vx = bVel ? -aVel->vx : -aVel->vx;
		if (bVel) bVel->vx = aVel ? -bVel->vx : -bVel->vx;

	} else {
		float signA = (aVel && aVel->vy != 0.f) ? (aVel->vy > 0.f ? 1.f : -1.f) : 1.f;
		float signB = (bVel && bVel->vy != 0.f) ? (bVel->vy > 0.f ? 1.f : -1.f) : 1.f;

		if (aVel) aPos->y -= minOverlapY * signA;
		if (bVel) bPos->y += minOverlapY * signB;

		if (aVel) aVel->vy = bVel ? -aVel->vy : -aVel->vy;
		if (bVel) bVel->vy = aVel ? -bVel->vy : -bVel->vy;
	}
}