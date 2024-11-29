#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "IMaterial.h"

class Reflective : public IMaterial {
    public:
        Reflective(Colord reflective);
        Colord computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked) override;

    public:
        Colord reflective;
};

#endif