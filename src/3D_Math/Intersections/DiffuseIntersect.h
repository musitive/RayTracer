#ifndef DIFFUSE_INTERSECTION_H
#define DIFFUSE_INTERSECTION_H

#include "AbstractIntersect.h"

class DiffuseIntersect : public AbstractIntersect {
    public:
        DiffuseIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        Colord computeColor(const Light& light, const int& depth) const override;
        bool isBlocked(const Point3D& light_position) const;
};

#endif