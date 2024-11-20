#include "Triangle.h"

const double K_EPSILON = .000000001;

Triangle::Triangle(Point3D v1, Point3D v2, Point3D v3) : v1(v1), v2(v2), v3(v3) {}

Point3D Triangle::findIntersectPosition(const Ray& ray, const bool& culling) const {
    Point3D edge_a = v2 - v1;
    Point3D edge_b = v3 - v1;

    Point3D pvec = cross_product(ray.direction, edge_b);

    float det = dot(edge_a, pvec);

    if (culling && det < K_EPSILON) return MISS;

    float invDet = 1 / det;

    Point3D tvec = ray.origin - v1;

    double u = dot(tvec, pvec) * invDet;

    if (u < 0 || u > 1) return MISS;
 
    Point3D qvec = cross_product(tvec, edge_a); 

    double v = dot(ray.direction, qvec) * invDet; 

    if (v < 0 || u + v > 1) return MISS; 
 
    double t = dot(edge_b, qvec) * invDet; 
 
    return ray.findPositionOnRay(t); 
}

Direction Triangle::computeNormal(Point3D p) {
    Direction a = v2 - v1;
    Direction b = v3 - v1;
    return cross_product(a, b);
}