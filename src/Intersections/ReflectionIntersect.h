#ifndef REFLECTION_INTERSECTION_H
#define REFLECTION_INTERSECTION_H

#include "AbstractIntersect.h"

class Reflection : public AbstractIntersection {
    public:
        Reflection(Actor* o, const Ray& r, const Point3D& p);
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

#endif