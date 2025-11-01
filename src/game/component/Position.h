#pragma once
#include "Component.h"

struct PositionComponent : Component {
    float x = 0;
    float y = 0;

    PositionComponent(float x_ = 0, float y_ = 0) : x(x_), y(y_) {}
};
