#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vec.h"
#include "Ray.h"

class Sphere : public Object {
    public:
        Sphere(Point3D center, double radius);
        Point3D findIntersectPosition(const Ray& ray, const bool& culling=true) const override;
        Direction computeNormal(Point3D position) override;

    private:
        Point3D center;
        double radius;
};

#endif