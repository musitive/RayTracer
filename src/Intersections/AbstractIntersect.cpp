#include "AbstractIntersect.h"

AbstractIntersection::AbstractIntersection(AbstractObject* o, const Ray& r)
    : obj(o), ray(r), point(o->findIntersection(r)), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(point)) {}

AbstractIntersection::AbstractIntersection(AbstractObject* o, const Ray& r, const Point3D& p)
    : obj(o), ray(r), point(p), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(p)) {}

AbstractIntersection::AbstractIntersection(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance)
    : obj(o), ray(r), point(p), distance(distance), normal(o->computeNormal(p)) {}

AbstractIntersection::AbstractIntersection(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance, const Direction& n)
    : obj(o), ray(r), point(p), distance(distance), normal(n) {}

AbstractIntersection::~AbstractIntersection() {}

double AbstractIntersection::findDistanceFromPoint(const Point3D& p) const {
    return length(point - p);
}

bool AbstractIntersection::isCloserThan(const AbstractIntersection* i) const {
    return distance < i->distance;
}

Direction AbstractIntersection::computeActorNormal() const {
    return obj->computeNormal(point);
}