#include "Ray.h"

Ray::Ray(Position eye, Direction s) : origin(eye), direction(s) {}

Position Ray::findPositionOnRay(const double& t) {
    return origin + direction * t;
}