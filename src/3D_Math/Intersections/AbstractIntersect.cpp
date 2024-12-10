#include "AbstractIntersect.h"

AbstractIntersect::AbstractIntersect(Actor* o, const Ray& r)
    : obj(o), ray(r), point(o->findIntersection(r)), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(point)) {}

AbstractIntersect::AbstractIntersect(Actor* o, const Ray& r, const Point3D& p)
    : obj(o), ray(r), point(p), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(p)) {}

AbstractIntersect::AbstractIntersect(Actor* o, const Ray& r, const Point3D& p, const double& distance)
    : obj(o), ray(r), point(p), distance(distance), normal(o->computeNormal(p)) {}

AbstractIntersect::AbstractIntersect(Actor* o, const Ray& r, const Point3D& p, const double& distance, const Direction& n)
    : obj(o), ray(r), point(p), distance(distance), normal(n) {}

AbstractIntersect::~AbstractIntersect() {}

double AbstractIntersect::findDistanceFromPoint(const Point3D& p) const {
    return length(point - p);
}

bool AbstractIntersect::isCloserThan(const AbstractIntersect* i) const {
    return distance < i->distance;
}

Direction AbstractIntersect::computeNormal() const {
    return obj->computeNormal(point);
}