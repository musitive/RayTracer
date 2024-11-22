#include "Sphere.h"
#include "Vec.h"

Sphere::Sphere(Point3D center, double radius) : center(center), radius(radius) {}

Point3D Sphere::findIntersectPosition(const Ray& ray, const bool& culling) const {
    // Distance between the center of the sphere and the origin of the ray
    // OC = S_c - r_0
    Point3D distance_to_origin = this->center - ray.origin;

    // tca = OC . r_d
    double tca = dot(distance_to_origin, ray.direction);

    if (tca < 0)
        return MISS;

    // d^2 = ||OC||^2 - tca^2
    double d_squared = dot(distance_to_origin, distance_to_origin) - tca * tca;
    double radius_squared = radius * radius;

    // if d^2 > r^2, the ray misses the sphere
    if (d_squared > radius_squared)
        return MISS;

    // thc = sqrt(r^2 - d^2)
    double thc = sqrt(radius_squared - d_squared);

    // if the origin of the ray is outside of the sphere
    double root = tca - thc;

    // else use the positive root
    // root = tca + thc;

    Point3D intersection = ray.findPositionOnRay(root);

    return intersection;
}

Direction Sphere::computeNormal(const Point3D& position) {
    return Direction(position - center);
}