#ifndef MISSED_INTERSECTION_H
#define MISSED_INTERSECTION_H

#include "AbstractIntersect.h"

class MissedIntersect : public AbstractIntersect {
    public:
        MissedIntersect(AbstractObject* o, const Ray& r);
        Colord computeColor(const Light& light, const int& depth) const override;
};

#endif