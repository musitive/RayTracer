#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "AbstractObject.h"
#include "Vec.h"
#include "RayTracer.h"

class RayTracer::AbstractIntersect {
    public:
        AbstractObject* o;
        Point3D p;
        double distance;
        Ray r;

        AbstractIntersect(AbstractObject* o, const Ray& r);
        AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance);
        virtual ~AbstractIntersect();

        double findDistanceFromPoint(const Point3D& p) const;
        bool isCloserThan(const AbstractIntersect* i) const;
        Direction computeNormal() const;
        virtual Colord computeColor(const Light& light, const int& depth) const = 0;
    
    protected:
        Environment* env;
};

class RayTracer::MissedIntersect : public RayTracer::AbstractIntersect {
    public:
        MissedIntersect(AbstractObject* o, const Ray& r);
        Colord computeColor(const Light& light, const int& depth) const override;
};

class RayTracer::ReflectionIntersect : public RayTracer::AbstractIntersect {
    public:
        ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        Colord computeColor(const Light& light, const int& depth) const override;
};

class RayTracer::DiffuseIntersect : public RayTracer::AbstractIntersect {
    public:
        DiffuseIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        Colord computeColor(const Light& light, const int& depth) const override;
        bool isBlocked(const Point3D& light_position) const;
};

#endif