#include "AbstractIntersect.h"
#include "RayTracer.h"

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r)
    : obj(o), ray(r), hit_point(o->findIntersection(r)), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(hit_point)) {}

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const vec3& p)
    : obj(o), ray(r), hit_point(p), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(p)) {}

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const vec3& p, const double& distance)
    : obj(o), ray(r), hit_point(p), distance(distance), normal(o->computeNormal(p)) {}

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const vec3& p, const double& distance, const Direction& n)
    : obj(o), ray(r), hit_point(p), distance(distance), normal(n) {}

AbstractIntersect::~AbstractIntersect() {}

double AbstractIntersect::findDistanceFromPoint(const vec3& p) const {
    return rt_lib::length(hit_point - p);
}

bool AbstractIntersect::isCloserThan(const AbstractIntersect* i) const {
    return distance < i->distance;
}

Direction AbstractIntersect::computeActorNormal() const {
    return obj->computeNormal(hit_point);
}

bool AbstractIntersect::isBlocked(const vec3 &light_position) const {
    return RayTracer::isObjectBlocked(light_position, hit_point, obj);
}