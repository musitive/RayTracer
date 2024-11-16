#include "Vec.h"

double length(const Position& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Position normalize(Position& vec) {
    double l = length(vec);
    if (l != 0)
        return Position(vec.x / l, vec.y / l, vec.z / l);
    else
        return vec;
}