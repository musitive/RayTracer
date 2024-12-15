#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec.h"

// forward declaration
class AbstractIntersection;

struct Light {
    RGBColor color;
    Point3D position;
};

class IMaterial {
    public:
        bool isReflective = false;
        virtual RGBColor computeColor(const AbstractIntersection* i, const Light& light, const bool& blocked) = 0;
};

#endif