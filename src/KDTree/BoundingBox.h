#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vec.h"
#include "Ray.h"

/**
 * @struct BoundingBox
 * @brief The BoundingBox struct represents a bounding box in 3D space. It contains a minimum and maximum bound.
 */
struct BoundingBox {
    vec3 min_bound;
    vec3 max_bound;

    BoundingBox() : min_bound(INF), max_bound(-INF) {}

    // Expands the bounding box to include another bounding box.
    void expand(const BoundingBox &other);

    // Checks if a ray intersects the bounding box using the slab method.
    bool doesIntersect(const Ray &ray) const;

    // Determines if two intervals overlap.
    bool intervalsOverlap(const double &min1, const double &max1, const double &min2, const double &max2) const;

    // Projects a ray onto an axis to find the intersection parameters.
    void calculateRayPositionOnAxis(double &t_min, double &t_max, const int &axis, const Ray &ray) const;

    //  Calculates the intersection parameter for a ray and a bounding box.
    double calculateIntersectionParameter(const int &axis, const vec3 &bound, const Ray &ray) const;

    // Determines the center of the bounding box.
    vec3 center() const;
};

#endif