#pragma once
#include "../entity/Entity.h"
#include <vector>

class CollisionSystem {
	public:
		void checkCollisions(std::vector<Entity*>& objects, float dt);
		void checkBoundaries(Entity& obj, float top, float bottom);

	private:
		void handleCollision(Entity& a, Entity& b, float dt);
};