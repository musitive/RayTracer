#include "Sphere.h"
#include "Vec.h"

Sphere::Sphere(const vec3 &center, const double &radius) : center(center), radius(radius) {
    box.min_bound = center - radius;
    box.max_bound = center + radius;
}

vec3 Sphere::findIntersection(const Ray &ray, const bool &culling) const {
    vec3 to_origin = center - ray.origin;                                       // OC = S_c - r_0
    double projection_length = dot(to_origin, ray.direction);                   // tca = OC . r_d

    if (projection_length < 0) return MISS;     // the projection of OC onto the ray is behind the origin

    double distance_squared = square(to_origin) - square(projection_length);    // d^2 = ||OC||^2 - r_d^2
    double radius_squared = square(radius); 

    if (distance_squared > radius_squared) return MISS;
    
    double half_chord_length = sqrt(radius_squared - distance_squared);         // thc = sqrt(r^2 - d^2)
    double root = projection_length - half_chord_length;                        // t0 = tca - thc

    return ray.findPoint(root);
}

Direction Sphere::computeNormal(const vec3 &position) {
    return Direction(position, center);
}