#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec.h"

// forward declaration
class AbstractIntersect;

struct Light {
    Colord color;
    Point3D position;
};

class IMaterial {
    public:
        bool isReflective = false;
        virtual Colord computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) = 0;
};

#endif