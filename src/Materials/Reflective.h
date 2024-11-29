#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "IMaterial.h"

class Reflective : public IMaterial {
    public:
        Reflective(Colord reflective);
        Colord computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) override;

    public:
        const Colord reflective;
};

#endif