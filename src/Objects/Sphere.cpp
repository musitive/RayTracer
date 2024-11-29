#include "Sphere.h"
#include "Vec.h"

Sphere::Sphere(Point3D center, double radius) : center(center), radius(radius) {}

Point3D Sphere::findIntersection(const Ray& ray, const bool& culling) const {
    // Distance between the center of the sphere and the origin of the ray
    // OC = S_c - r_0
    Vector3D to_origin = center - ray.origin;

    // tca = OC . r_d
    double projection_length = dot(to_origin, ray.direction);

    // if tca < 0, the projection of OC onto the ray is behind the origin
    if (projection_length < 0) return MISS;

    // d^2 = ||OC||^2 - r_d^2
    double distance_squared = square(to_origin) - square(projection_length);
    double radius_squared = square(radius); // r^2

    // if d^2 > r^2, the ray misses the sphere
    if (distance_squared > radius_squared) return MISS;

    // thc = sqrt(r^2 - d^2)
    double half_chord_length = sqrt(radius_squared - distance_squared);

    // t0 = tca - thc
    double root = projection_length - half_chord_length;

    // the root exists if the ray intersects the sphere
    return ray.findPoint(root);
}

Direction Sphere::computeNormal(const Point3D& position) {
    return Direction(position, center);
}