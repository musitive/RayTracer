#include "Position.h"

Position normalize(const Position& vec) {
    double l = length(vec);
    if (l != 0)
        return Position(vec.x / l, vec.y / l, vec.z / l);
    else
        return vec;
}

double length(const Position& vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

double dot(Position& vec1, Position& vec2) {
    Position v = vec1 * vec2;
    return v.x + v.y + v.z;
}

Position cross_product(Position& vec1, Position& vec2) {
    return Position(vec1.y * vec2.z - vec1.z * vec2.y,
                   vec1.z * vec2.x - vec1.x * vec2.z,
                   vec1.x * vec2.y - vec1.y * vec2.x);
}