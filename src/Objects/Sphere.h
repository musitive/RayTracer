#ifndef SPHERE_H
#define SPHERE_H

#include "AbstractObject.h"
#include "Vec.h"
#include "Ray.h"

class Sphere : public AbstractObject {
    public:
        Sphere(Point3D center, double radius);
        Point3D findIntersectPosition(const Ray& ray, const bool& culling=true) const override;
        Direction computeNormal(Point3D position) override;

    private:
        Point3D center;
        double radius;
};

#endif