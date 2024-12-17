#include "BoundingBox.h"

#define DIMENSIONS 3
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2        // @todo: Replace with an enum

// Expands the bounding box to include another bounding box.
void BoundingBox::expand(const BoundingBox &other)
{
    min_bound = rt_lib::min(min_bound, other.min_bound);
    max_bound = rt_lib::max(max_bound, other.max_bound);
}

// Checks if a ray intersects the bounding box using the slab method.
bool BoundingBox::doesIntersect(const Ray &ray) const {
    double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;

    // Calculate the intersection parameters for each axis
    calculateRayPositionOnAxis(tx_min, tx_max, X_AXIS, ray);
    calculateRayPositionOnAxis(ty_min, ty_max, Y_AXIS, ray);

    // If the intervals don't overlap, the ray doesn't intersect the bounding box
    if (!intervalsOverlap(tx_min, tx_max, ty_min, ty_max)) return false;

    // Create the widest interval from the x and y intervals
    if (ty_min > tx_min) tx_min = ty_min;
    if (ty_max < tx_max) tx_max = ty_max;

    calculateRayPositionOnAxis(tz_min, tz_max, Z_AXIS, ray);        // Lazy evaluation

    // If the intervals don't overlap, the ray doesn't intersect the bounding box
    if (!intervalsOverlap(tx_min, tx_max, tz_min, tz_max)) return false;

    return true;
}

// Determines if two intervals overlap.
bool BoundingBox::intervalsOverlap(const double &min1, const double &max1, const double &min2, const double &max2) const {
    return !(min1 > max2 || min2 > max1);
}

// Projects a ray onto an axis to find the intersection parameters.
void BoundingBox::calculateRayPositionOnAxis(double &t_min, double &t_max, const int &axis, const Ray &ray) const
{
    t_min = calculateIntersectionParameter(axis, min_bound, ray);
    t_max = calculateIntersectionParameter(axis, max_bound, ray);
    if (t_min > t_max) std::swap(t_min, t_max);
}

//  Calculates the intersection parameter for a ray and a bounding box.
double BoundingBox::calculateIntersectionParameter(const int &axis, const vec3 &bound, const Ray &ray) const {
    return (bound[axis] - ray.origin[axis]) / ray.direction[axis];
}

// Determines the center of the bounding box.
vec3 BoundingBox::center() const {
    return (min_bound + max_bound) / 2;
}