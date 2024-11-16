#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vec.h"
#include "Ray.h"

class Sphere : public Object {
    private:
        Position center;
        double radius;

    public:
        Sphere(Position center, double radius);

        Position calculateIntersection(const Ray& ray, const bool& culling=true) override;
        Direction computeNormal(Position position) override;
};

#endif