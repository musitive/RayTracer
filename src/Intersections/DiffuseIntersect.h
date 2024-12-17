#ifndef DIFFUSE_INTERSECTION_H
#define DIFFUSE_INTERSECTION_H

#include "AbstractIntersect.h"

class Absorption : public AbstractIntersect {
    public:
        Absorption(AbstractObject* o, const Ray& r, const vec3& p);
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

#endif