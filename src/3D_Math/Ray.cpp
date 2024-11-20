#include "Ray.h"

Ray::Ray() : origin(Point3D()), direction(Direction(Point3D())) {}

Ray::Ray(Point3D eye, Direction s) : origin(eye), direction(s) {}

Point3D Ray::findPositionOnRay(double t) const {
    return origin + direction * t;
}