#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "IMaterial.h"

class Reflective : public IMaterial {
    public:
        Reflective(RGBColor reflective);
        bool isReflective() override { return true; }
        RGBColor computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) override;

    private:
        const RGBColor reflective;
};

#endif