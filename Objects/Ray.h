#pragma once

#include "Position.h"
#include "Direction.h"

class Ray {
    public:
        Position origin;
        Direction direction;

        Ray(Position eye, Direction s);
        Position findPositionOnRay(const double& t);
};