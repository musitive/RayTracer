#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "AbstractObject.h"
#include "Vec.h"
#include "RayTracer.h"

class RayTracer::AIntersect {
    public:
        AbstractObject* o;
        Point3D p;
        double distance;
        Ray r;

        AIntersect(AbstractObject* o, const Ray& r);
        AIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        AIntersect(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance);

        double findDistanceFromPoint(const Point3D& p) const;
        bool isCloserThan(const AIntersect* i) const;
        Direction computeNormal() const;
        virtual Colord computeColor(const Light& light, const Colord& ambient_light, const int& depth) const = 0;
    
    protected:
        Environment* env;
};

class RayTracer::MissedIntersect : public RayTracer::AIntersect {
    public:
        MissedIntersect(AbstractObject* o, const Ray& r);
        Colord computeColor(const Light& light, const Colord& ambient_light, const int& depth) const override;
};

class RayTracer::ReflectionIntersect : public RayTracer::AIntersect {
    public:
        ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        Colord computeColor(const Light& light, const Colord& ambient_light, const int& depth) const override;
};

class RayTracer::DiffuseIntersect : public RayTracer::AIntersect {
    public:
        DiffuseIntersect(AbstractObject* o, const Ray& r, const Point3D& p);
        Colord computeColor(const Light& light, const Colord& ambient_light, const int& depth) const override;
        bool isBlocked(const Point3D& light_position) const;
};

#endif