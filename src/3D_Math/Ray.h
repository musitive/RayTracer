#ifndef RAY_H
#define RAY_H

#include "Vec.h"
#include "Direction.h"

struct Ray {
    public:
        vec3 origin;            // r_0
        Direction direction;    // r_d

        Ray();
        Ray(vec3 eye, Direction s);
        vec3 findPoint(const double &distance) const;
};

#endif