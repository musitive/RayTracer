#ifndef DIRECTION_H
#define DIRECTION_H

#include "Vec.h"

/**
 * @class Direction
 * @brief The Direction class is a subclass of vec3 that represents a direction vector in 3D space
 */
class Direction : public vec3 {
    public:
        // Constructor normalizes the vector
        Direction(const vec3 &from, const vec3 &to = vec3(0));
};

#endif