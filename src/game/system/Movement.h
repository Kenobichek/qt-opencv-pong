#pragma once
#include <vector>
#include "../entity/Entity.h"
#include "../component/Position.h"
#include "../component/Velocity.h"

class MovementSystem {
	public:
		void update(std::vector<Entity>& objects, float dt);
};
