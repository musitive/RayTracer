#ifndef REFLECTION_INTERSECTION_H
#define REFLECTION_INTERSECTION_H

#include "AbstractIntersect.h"

class Reflection : public AbstractIntersect {
    public:
        Reflection(AbstractObject* o, const Ray& r, const vec3& p);
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

#endif