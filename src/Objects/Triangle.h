#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Vec.h"
#include "Ray.h"

class Triangle : public Object {
    public:
        Triangle(Point3D v1, Point3D v2, Point3D v3);
        Point3D findIntersectPosition(const Ray& ray, const bool& culling=true) const override;
        Direction computeNormal(Point3D p) override;

    private:
        Point3D v1, v2, v3;
};

#endif