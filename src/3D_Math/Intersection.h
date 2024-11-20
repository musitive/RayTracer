#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Object.h"
#include "Vec.h"

class Intersection {
    public:
        Intersection();
        Intersection(Object* o, const Ray& r);

        double findDistanceFromPoint(Point3D p) const;
        bool isCloserThan(const Intersection& i) const;
        Direction computeNormal() const;
        Colord computeColor(const Light& light, const bool& blocked, const Colord& ambient_light) const;

        double getDistance() const;
        Object* getObject() const;
        Ray getRay() const;
        Point3D getPosition() const;

    private:
        Object* o;
        Point3D p;
        double distance;
        Ray r;
};

#endif