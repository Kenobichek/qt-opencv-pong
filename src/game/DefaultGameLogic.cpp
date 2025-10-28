#include "DefaultGameLogic.h"
#include <algorithm>
#include <iostream>

void DefaultGameLogic::update(GameState& state, const std::vector<Rect>& hands, float dt) {
	updatePaddles(state, hands);
	updateBall(state, dt);
	checkCollisions(state);
}

void DefaultGameLogic::reset(GameState& state) {
	state.scores = {0, 0};
	state.ball.x = state.screen.width() / 2.f;
	state.ball.y = state.screen.height() / 2.f;
	state.ball.vx = 200.f;
	state.ball.vy = 150.f;
}

void DefaultGameLogic::updatePaddles(GameState& state, const std::vector<Rect>& hands) {

	state.paddles.resize(hands.size());

	for (size_t i = 0; i < hands.size(); ++i) {
		state.paddles[i].x = hands[i].x;
		state.paddles[i].y = hands[i].y;
		state.paddles[i].width = hands[i].width;
		state.paddles[i].height = hands[i].height;
	}
}

void DefaultGameLogic::updateBall(GameState& state, const float dt) {
	state.ball.x += state.ball.vx * dt;
	state.ball.y += state.ball.vy * dt;

	if (state.ball.y - state.ball.radius < 0 || state.ball.y + state.ball.radius > state.screen.height()) {
		state.ball.vy *= -1;
	}

	if (state.ball.x < 0) {
		state.scores[1]++;
		reset(state);
	} else if (state.ball.x > state.screen.width()) {
		state.scores[0]++;
		reset(state);
	}
}

void DefaultGameLogic::checkCollisions(GameState& state) {
	auto& ball = state.ball;

	for (auto& paddle : state.paddles) {
		if (ball.y + ball.radius < paddle.y || ball.y - ball.radius > paddle.y + paddle.height)
			continue;

		bool hitLeft = ball.vx < 0 && ball.x - ball.radius < paddle.x + paddle.width && ball.x - ball.radius > paddle.x;
		bool hitRight = ball.vx > 0 && ball.x + ball.radius > paddle.x && ball.x + ball.radius < paddle.x + paddle.width;

		if (hitLeft || hitRight) {
			if (hitLeft) ball.x = paddle.x + paddle.width + ball.radius;
			else ball.x = paddle.x - ball.radius;

			ball.vx *= -1;

			float hitPos = (ball.y - paddle.y) / paddle.height - 0.5f;
			ball.vy += hitPos * 100;

			break;
		}
	}
}
