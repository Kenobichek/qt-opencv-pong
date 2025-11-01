#include "CameraInput.h"
#include "../component/CameraInput.h"
#include "../component/Position.h"
#include "../component/Collider.h"

void CameraInputSystem::update(std::vector<Entity>& paddles, const std::vector<Rect>& hands) {
	for(size_t i = 0; i < paddles.size(); ++i) {
		auto input = paddles[i].getComponent<CameraInputComponent>();
		auto pos = paddles[i].getComponent<PositionComponent>();
		auto col = paddles[i].getComponent<ColliderComponent>();

		if (!input || !pos || !col) continue;

		int handIdx = i;
		if (handIdx < 0 || handIdx >= static_cast<int>(hands.size())) {
			col->width = 0;
			col->height = 0;
			continue;
		}

		const auto& hand = hands[handIdx];
		
		pos->y = hand.y;
		pos->x = hand.x;
		col->width = hand.width;
		col->height = hand.height;
	}
}