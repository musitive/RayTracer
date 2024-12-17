#ifndef SPHERE_H
#define SPHERE_H

#include "AbstractObject.h"
#include "Vec.h"
#include "Ray.h"

class Sphere : public AbstractObject {
    public:
        Sphere(const vec3 &center, const double &radius);
        vec3 findIntersection(const Ray &ray, const bool &culling=true) const override;
        Direction computeNormal(const vec3 &position) override;

    private:
        vec3 center;
        double radius;
};

#endif