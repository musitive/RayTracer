#ifndef RAY_H
#define RAY_H

#include "Vec.h"

class Ray {
    public:
        Position origin;        // r_0
        Direction direction;    // r_d

        Ray(Position eye, Direction s) : origin(eye), direction(s) {}
        Position findPositionOnRay(double t) {
            return origin + direction * t;
        }
};

#endif