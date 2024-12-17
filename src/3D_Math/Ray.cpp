#include "Ray.h"

Ray::Ray() : origin(vec3()), direction(Direction(vec3(), vec3())) {}

Ray::Ray(vec3 eye, Direction s) : origin(eye), direction(s) {}

vec3 Ray::findPoint(const double &distance) const {
    return origin + direction * distance;
}