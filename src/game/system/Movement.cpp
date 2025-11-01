#include "Movement.h"

void MovementSystem::update(std::vector<Entity>& objects, float dt) {
	for (auto& obj : objects) {
		auto pos = obj.getComponent<PositionComponent>();
		auto vel = obj.getComponent<VelocityComponent>();

		if (pos && vel) {
			pos->x += vel->vx * dt;
			pos->y += vel->vy * dt;
		}
	}
}