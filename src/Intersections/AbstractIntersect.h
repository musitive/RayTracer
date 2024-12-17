#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "AbstractObject.h"
#include "Vec.h"

class AbstractIntersect {
    public:
        AbstractObject* obj;
        vec3 hit_point;
        double distance;
        Ray ray;
        Direction normal;

        AbstractIntersect(AbstractObject* o, const Ray& r);
        AbstractIntersect(AbstractObject* o, const Ray& r, const vec3& p);
        AbstractIntersect(AbstractObject* o, const Ray& r, const vec3& p, const double& distance);
        AbstractIntersect(AbstractObject* o, const Ray& r, const vec3& p, const double& distance, const Direction& n);
        virtual ~AbstractIntersect();

        double findDistanceFromPoint(const vec3& p) const;
        bool isCloserThan(const AbstractIntersect* i) const;
        Direction computeActorNormal() const;
        virtual RGBColor computeColor(const Light& light, const int& depth) const = 0;
        bool isBlocked(const vec3 &light_position) const;
};

#endif