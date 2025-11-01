#pragma once
#include <vector>
#include "../../dto/Screen.h"
#include "../entity/Entity.h"
#include "../component/Position.h"
#include "../component/Collider.h"
#include "../component/Velocity.h"
#include "../component/CameraInput.h"

struct GameState {
	Screen screen;
	std::vector<Entity> paddles;
	std::vector<Entity> balls;
	std::vector<int> scores;

	GameState() {
		Entity paddle1;
		paddle1.addComponent<PositionComponent>(50.0f, screen.height() / 2.f - 40.f / 2.f);
		paddle1.addComponent<ColliderComponent>();
		paddle1.addComponent<CameraInputComponent>();
		paddles.push_back(paddle1);

		Entity paddle2;
		paddle2.addComponent<PositionComponent>(screen.width() - 50.0f - 10.0f, screen.height() / 2.f - 40.f / 2.f);
		paddle2.addComponent<ColliderComponent>();
		paddle2.addComponent<CameraInputComponent>();
		paddles.push_back(paddle2);

		Entity ball;
		ball.addComponent<PositionComponent>(screen.width() / 2.f, screen.height() / 2.f);
		ball.addComponent<VelocityComponent>(300.0f, 150.0f);
		ball.addComponent<ColliderComponent>(16.0f, 16.0f);
		balls.push_back(ball);

		scores = {0, 0};
	}
};
