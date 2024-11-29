#ifndef REFLECTION_INTERSECTION_H
#define REFLECTION_INTERSECTION_H

#include "AbstractIntersect.h"

class ReflectionIntersect : public AbstractIntersect {
    public:
        ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        Colord computeColor(const Light& light, const int& depth) const override;
};

#endif