#ifndef MISSED_INTERSECTION_H
#define MISSED_INTERSECTION_H

#include "AbstractIntersect.h"

class Miss : public AbstractIntersection {
    public:
        Miss(AbstractObject* o, const Ray& r);
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

#endif