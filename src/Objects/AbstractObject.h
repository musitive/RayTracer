#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "IMaterial.h"
#include "Vec.h"
#include "Ray.h"

class Actor {
    public:
        void setMaterial(IMaterial* material);
        IMaterial* getMaterial() const;

        virtual Direction computeNormal(const Point3D& p) = 0;
        virtual Point3D findIntersection(const Ray& ray, const bool& culling=true) const = 0;

        bool isBlocking(const Ray& to_light, const Point3D& light_position, const double& distance);

    private:
        IMaterial* material;
};

#endif