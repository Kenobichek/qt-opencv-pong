#include <gtest/gtest.h>
#include "../src/game/system/Collision.h"
#include "../src/game/entity/Entity.h"
#include "../src/game/component/Position.h"
#include "../src/game/component/Velocity.h"
#include "../src/game/component/Collider.h"

class CollisionSystemTest : public ::testing::Test {
	protected:
        CollisionSystem collisionSystem;

        Entity createEntity(float x, float y, float vx, float vy, float width, float height) {
            Entity e;
            e.addComponent<PositionComponent>(x, y);
            e.addComponent<VelocityComponent>(vx, vy);
            e.addComponent<ColliderComponent>(width, height);
            return e;
        }
};

// Top boundary
TEST_F(CollisionSystemTest, AboveTopBoundaryInvertsVelocity) {
    auto e = createEntity(0.0f, -1.0f, 300.0f, 150.0f, 16.0f, 16.0f);
    collisionSystem.checkBoundaries(e, 0.0f, 10.0f);

    auto pos = e.getComponent<PositionComponent>();
    auto vel = e.getComponent<VelocityComponent>();

    EXPECT_EQ(pos->y, 0.0f);
    EXPECT_EQ(vel->vy, -150.0f);
}

// Bottom boundary
TEST_F(CollisionSystemTest, BelowBottomBoundaryInvertsVelocity) {
    auto e = createEntity(0.0f, 11.0f, 100.0f, -50.0f, 16.0f, 16.0f);
    collisionSystem.checkBoundaries(e, 0.0f, 10.0f);

    auto pos = e.getComponent<PositionComponent>();
    auto vel = e.getComponent<VelocityComponent>();

    // Should clamp to bottom boundary minus collider height
    EXPECT_EQ(pos->y, 10.0f - 16.0f);
    EXPECT_EQ(vel->vy, 50.0f);
}

// Left boundary
TEST_F(CollisionSystemTest, BeyondLeftBoundaryInvertsVelocity) {
    auto e = createEntity(-5.0f, 5.0f, -200.0f, 0.0f, 16.0f, 16.0f);
    collisionSystem.checkBoundaries(e, 0.0f, 10.0f);

    auto pos = e.getComponent<PositionComponent>();
    auto vel = e.getComponent<VelocityComponent>();

    EXPECT_EQ(pos->x, -5.0f);
    EXPECT_EQ(vel->vx, -200.0f);
}

// Right boundary
TEST_F(CollisionSystemTest, BeyondRightBoundaryInvertsVelocity) {
    auto e = createEntity(15.0f, 5.0f, 50.0f, 0.0f, 16.0f, 16.0f);
    collisionSystem.checkBoundaries(e, 0.0f, 10.0f);

    auto pos = e.getComponent<PositionComponent>();
    auto vel = e.getComponent<VelocityComponent>();

    EXPECT_EQ(pos->x, 15.0f);
    EXPECT_EQ(vel->vx, 50.0f);
}

// No collision
TEST_F(CollisionSystemTest, InsideBoundariesVelocityUnchanged) {
    auto e = createEntity(2.0f, 3.0f, 10.0f, 20.0f, 10.0f, 10.0f);
    collisionSystem.checkBoundaries(e, 0.0f, 25.0f);

    auto pos = e.getComponent<PositionComponent>();
    auto vel = e.getComponent<VelocityComponent>();

    EXPECT_EQ(pos->x, 2.0f);
    EXPECT_EQ(pos->y, 3.0f);
    EXPECT_EQ(vel->vx, 10.0f);
    EXPECT_EQ(vel->vy, 20.0f);
}
