#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "AbstractObject.h"
#include "Vec.h"

class AbstractIntersection {
    public:
        AbstractObject* obj;
        Point3D point;
        double distance;
        Ray ray;
        Direction normal;

        AbstractIntersection(AbstractObject* o, const Ray& r);
        AbstractIntersection(AbstractObject* o, const Ray& r, const Point3D& p);
        AbstractIntersection(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance);
        AbstractIntersection(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance, const Direction& n);
        virtual ~AbstractIntersection();

        double findDistanceFromPoint(const Point3D& p) const;
        bool isCloserThan(const AbstractIntersection* i) const;
        Direction computeActorNormal() const;
        virtual RGBColor computeColor(const Light& light, const int& depth) const = 0;
};

#endif