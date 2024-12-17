#ifndef MISSED_INTERSECTION_H
#define MISSED_INTERSECTION_H

#include "AbstractIntersect.h"

class Miss : public AbstractIntersect {
    public:
        Miss(AbstractObject* o = nullptr, const Ray& r = Ray());
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

#endif