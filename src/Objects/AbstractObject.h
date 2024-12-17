#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "IMaterial.h"
#include "Vec.h"
#include "Ray.h"
#include "BoundingBox.h"

class AbstractObject {
    public:
        void setMaterial(IMaterial* material);
        IMaterial* getMaterial() const;

        virtual Direction computeNormal(const vec3 &p) = 0;
        virtual vec3 findIntersection(const Ray &ray, const bool &culling=true) const = 0;

        bool isBlocking(const Ray &to_light, const vec3 &light_position, const double &distance);
        BoundingBox getBoundingBox() const { return box; }

        // Forwards the call to the material to determine if the object is reflective.
        bool isReflective() const { return material->isReflective(); }

        // Computes the color of the object at an intersection point.
        RGBColor computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked = false) {
            return material->computeColor(i, light, blocked);
        }

    protected:
        BoundingBox box;

    private:
        IMaterial* material;
};

#endif