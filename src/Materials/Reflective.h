#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "IMaterial.h"

class Reflective : public IMaterial {
    public:
        Reflective(RGBColor reflective);
        RGBColor computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) override;

    public:
        const RGBColor reflective;
};

#endif