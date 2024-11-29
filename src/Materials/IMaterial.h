#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec.h"

struct Light {
    Colord color;
    Point3D position;
};

class IMaterial {
    public:
        bool isReflective = false;
        virtual Colord computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked) = 0;
};

#endif