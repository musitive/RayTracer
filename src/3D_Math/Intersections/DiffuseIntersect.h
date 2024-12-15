#ifndef DIFFUSE_INTERSECTION_H
#define DIFFUSE_INTERSECTION_H

#include "AbstractIntersect.h"

class Absorption : public AbstractIntersection {
    public:
        Absorption(Actor* o, const Ray& r, const Point3D& p);
        RGBColor computeColor(const Light& light, const int& depth) const override;
        bool isBlocked(const Point3D& light_position) const;
};

#endif