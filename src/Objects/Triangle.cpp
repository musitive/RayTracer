#include "Triangle.h"

const double K_EPSILON = .000000001;

Triangle::Triangle(const vec3 &a, const vec3 &b, const vec3 &c) :
    v1(a), v2(b), v3(c), normal(cross_product(b-a, c-a))
{
    box.min_bound = rt_lib::min(rt_lib::min(v1, v2), v3);
    box.max_bound = rt_lib::max(rt_lib::max(v1, v2), v3);
}

// Finds the intersection of a ray with a triangle using the Moller-Trumbore algorithm.
vec3 Triangle::findIntersection(const Ray& ray, const bool& culling) const {
    vec3 edge1 = v2 - v1;
    vec3 edge2 = v3 - v1;

    vec3 P = cross_product(ray.direction, edge2);                           // P = D x E2
    float determinant = dot(edge1, P);                                      // det = E1 . P

    if (culling && isParallel(determinant)) return MISS;

    float inverse_determinant = 1 / determinant;    // division is expensive, so do it once
    vec3 T = ray.origin - v1;                                               // T = r_0 - A
    double u = computeBarycentric(T, P, inverse_determinant);               // u = T . P / det

    if (isOutsideTriangle(u)) return MISS;

    vec3 Q = cross_product(T, edge1);                                       // Q = T x E1
    double v = computeBarycentric(ray.direction, Q, inverse_determinant);   // v = D . Q / det

    if (isOutsideTriangle(u, v)) return MISS;

    double intersection_distance = dot(edge2, Q) * inverse_determinant;     // t = E2 . Q / det
    return ray.findPoint(intersection_distance);
}

// The normal of a triangle is the same for all points on the triangle.
Direction Triangle::computeNormal(const vec3 &p) {
    return normal;
}

// Computes the barycentric coordinate of a point on a triangle.
inline double Triangle::computeBarycentric(const vec3& a, const vec3& b, const double& inverse_determinant) const {
    return dot(a, b) * inverse_determinant;
}

// Determines if the determinant is close to zero, indicating that the ray.
inline bool Triangle::isParallel(const float &determinant) const {
    return determinant < K_EPSILON;
}

// the point is outside the if the barycentric coordinate is less than zero or greater than one.
inline bool Triangle::isOutsideTriangle(const double &u) const {
    return u < 0 || u > 1;
}

// the point is outside the if the barycentric coordinate is less than zero or greater than one.
inline bool Triangle::isOutsideTriangle(const double &u, const double &v) const {
    return v < 0 || u + v > 1;
}