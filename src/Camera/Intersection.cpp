#include "Intersection.h"
#include "Scene.h"

RayTracer::AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r) {
    env = Scene::getInstance()->getEnvironment();
    this->o = o;
    this->r = r;
    this->p = o->findIntersection(r);
    distance = findDistanceFromPoint(r.origin);
}

RayTracer::AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p) {
    env = Scene::getInstance()->getEnvironment();
    this->o = o;
    this->r = r;
    this->p = p;
    distance = findDistanceFromPoint(r.origin);
}

RayTracer::AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance) {
    env = Scene::getInstance()->getEnvironment();
    this->o = o;
    this->r = r;
    this->p = p;
    // this->p = o->findIntersection(r);
    this->distance = distance;
    // distance = findDistanceFromPoint(r.origin);
}

RayTracer::AbstractIntersect::~AbstractIntersect() {}

double RayTracer::AbstractIntersect::findDistanceFromPoint(const Point3D& p) const {
    return length(this->p - p);
}

bool RayTracer::AbstractIntersect::isCloserThan(const AbstractIntersect* i) const {
    return distance < i->distance;
}

Direction RayTracer::AbstractIntersect::computeNormal() const {
    return o->computeNormal(p);
}

RayTracer::MissedIntersect::MissedIntersect(AbstractObject* o, const Ray& r) : AbstractIntersect(o, r, MISS, INF) {}

Colord RayTracer::MissedIntersect::computeColor(const Light& light, const int& depth) const {
    return env->background;
}

RayTracer::ReflectionIntersect::ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AbstractIntersect(o, r, p) {}

Colord RayTracer::ReflectionIntersect::computeColor(const Light& light, const int& depth) const {
    Direction normal = computeNormal();
    double dt = dot(r.direction, normal);
    Direction reflection_direction = normal * (dt * 2) - r.direction;
    Ray reflection(p, -reflection_direction);

    Colord cd = o->computeColor(r.origin, p, light, false);
    Colord ct = RayTracer::trace(reflection, o, depth+1);

    return ct * cd;
}

RayTracer::DiffuseIntersect::DiffuseIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AbstractIntersect(o, r, p) {}

Colord RayTracer::DiffuseIntersect::computeColor(const Light& light, const int& depth) const {
    bool blocked = isBlocked(light.position);
    
    return o->computeColor(r.origin, p, light, blocked);
}

bool RayTracer::DiffuseIntersect::isBlocked(const Point3D& light_position) const {
    Direction direction_to_light = light_position - p;
    double distance = length(light_position - p);
    Ray to_light(p, direction_to_light);

    for (AbstractObject* obj: env->env)
        if (obj != o && obj->isBlocking(to_light, light_position, distance))
            return true;

    return false;
}