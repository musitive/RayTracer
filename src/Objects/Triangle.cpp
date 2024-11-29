#include "Triangle.h"

const double K_EPSILON = .000000001;

Triangle::Triangle(Point3D a, Point3D b, Point3D c)
    : v1(a), v2(b), v3(c), edge1(b - a), edge2(c - a), normal(cross_product(edge1, edge2)) {}

// Moller-Trumbore algorithm
Point3D Triangle::findIntersection(const Ray& ray, const bool& culling) const {
    // Cramer's rule
    // P = D x E2
    Vector3D P = cross_product(ray.direction, edge2);

    // det = E1 . P
    float determinant = dot(edge1, P);

    if (culling && isParallel(determinant)) return MISS;

    // division is expensive, so do it once
    float inverse_determinant = 1 / determinant;

    // T = O - V1
    Vector3D T = ray.origin - v1;

    // u = T . P / det
    Barycentric u = computeBarycentricCoordinate(T, P, inverse_determinant);
    if (isOutsideTriangle(u)) return MISS;

    // Q = T x E1
    Vector3D Q = cross_product(T, edge1);

    // v = D . Q / det
    Barycentric v = computeBarycentricCoordinate(ray.direction, Q, inverse_determinant);
    if (isOutsideTriangle(u, v)) return MISS;

    // t = E2 . Q / det
    double intersection_distance = dot(edge2, Q) * inverse_determinant;
    return ray.findPoint(intersection_distance);
}

Barycentric Triangle::computeBarycentricCoordinate(const Vector3D& a, const Vector3D& b, const double& inverse_determinant) const {
    return dot(a, b) * inverse_determinant;
}

bool Triangle::isParallel(const float& determinant) const {
    return determinant < K_EPSILON;
}

bool Triangle::isOutsideTriangle(const Barycentric& u) const {
    return u < 0 || u > 1;
}

bool Triangle::isOutsideTriangle(const Barycentric& u, const Barycentric& v) const {
    return v < 0 || u + v > 1;
}

Direction Triangle::computeNormal(const Point3D& p) {
    return normal;
}