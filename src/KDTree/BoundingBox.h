#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vec.h"
#include "Ray.h"

struct BoundingBox {
    Point3D min_bound;
    Point3D max_bound;

    BoundingBox() : min_bound(INF), max_bound(-INF) {}

    void expand(const BoundingBox& other) {
       min_bound = min(min_bound, other.min_bound);
       max_bound = max(max_bound, other.max_bound);
    }

    bool intersects(const Ray& ray) const {
        // Implement ray-box intersection test
        double tmin = (min_bound.x - ray.origin.x) / ray.direction.x;
        double tmax = (max_bound.x - ray.origin.x) / ray.direction.x;

        if (tmin > tmax) std::swap(tmin, tmax);

        double tymin = (min_bound.y - ray.origin.y) / ray.direction.y;
        double tymax = (max_bound.y - ray.origin.y) / ray.direction.y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
            tmin = tymin;

        if (tymax < tmax)
            tmax = tymax;

        double tzmin = (min_bound.z - ray.origin.z) / ray.direction.z;
        double tzmax = (max_bound.z - ray.origin.z) / ray.direction.z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        return true;
    }

    Point3D center() const {
        return (min_bound + max_bound) / 2;
    }
};

#endif