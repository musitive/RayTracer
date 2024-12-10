#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "AbstractObject.h"
#include "Vec.h"

class AbstractIntersect {
    public:
        Actor* obj;
        Point3D point;
        double distance;
        Ray ray;
        Direction normal;

        AbstractIntersect(Actor* o, const Ray& r);
        AbstractIntersect(Actor* o, const Ray& r, const Point3D& p);
        AbstractIntersect(Actor* o, const Ray& r, const Point3D& p, const double& distance);
        AbstractIntersect(Actor* o, const Ray& r, const Point3D& p, const double& distance, const Direction& n);
        virtual ~AbstractIntersect();

        double findDistanceFromPoint(const Point3D& p) const;
        bool isCloserThan(const AbstractIntersect* i) const;
        Direction computeNormal() const;
        virtual RGBColor computeColor(const Light& light, const int& depth) const = 0;
};

#endif