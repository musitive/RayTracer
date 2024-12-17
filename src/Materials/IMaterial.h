#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec.h"

// forward declaration
class AbstractIntersect;

struct Light {
    RGBColor color;
    vec3 position;
};

class IMaterial {
    public:
        virtual bool isReflective() = 0;
        virtual RGBColor computeColor(const AbstractIntersect *i, const Light &light, const bool &blocked) = 0;
};

#endif