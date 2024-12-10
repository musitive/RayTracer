#ifndef MISSED_INTERSECTION_H
#define MISSED_INTERSECTION_H

#include "AbstractIntersect.h"

class MissedIntersect : public AbstractIntersect {
    public:
        MissedIntersect(Actor* o, const Ray& r);
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

#endif