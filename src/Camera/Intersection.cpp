#include "Intersection.h"
#include "Scene.h"

RayTracer::AIntersect::AIntersect(AbstractObject* o, const Ray& r) {
    env = Scene::getInstance()->getEnvironment();
    this->o = o;
    this->r = r;
    this->p = o->findIntersectPosition(r);
    distance = findDistanceFromPoint(r.origin);
}

RayTracer::AIntersect::AIntersect(AbstractObject* o, const Ray& r, const Point3D& p) {
    env = Scene::getInstance()->getEnvironment();
    this->o = o;
    this->r = r;
    this->p = p;
    distance = findDistanceFromPoint(r.origin);
}

RayTracer::AIntersect::AIntersect(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance) {
    env = Scene::getInstance()->getEnvironment();
    this->o = o;
    this->r = r;
    this->p = p;
    // this->p = o->findIntersectPosition(r);
    this->distance = distance;
    // distance = findDistanceFromPoint(r.origin);
}

double RayTracer::AIntersect::findDistanceFromPoint(const Point3D& p) const {
    return length(this->p - p);
}

bool RayTracer::AIntersect::isCloserThan(const AIntersect* i) const {
    return distance < i->distance;
}

Direction RayTracer::AIntersect::computeNormal() const {
    return o->computeNormal(p);
}

// Colord RayTracer::AbstractIntersection::computeColor(const Light& light, const bool& blocked, const Colord& ambient_light) const {
//     return o->computeColor(r.origin, p, light, blocked, ambient_light);
// }

RayTracer::MissedIntersection::MissedIntersection(AbstractObject* o, const Ray& r) : AIntersect(o, r, MISS, INF) {}

Colord RayTracer::MissedIntersection::computeColor(const Light& light, const Colord& ambient_light, const int& depth) const {
    return env->background;
}

RayTracer::ReflectionIntersect::ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AIntersect(o, r, p) {}

Colord RayTracer::ReflectionIntersect::computeColor(const Light& light, const Colord& ambient_light, const int& depth) const {
    Direction normal = computeNormal();
    double dt = dot(r.direction, normal);
    Direction reflection_direction = normal * (dt * 2) - r.direction;
    Ray reflection(p, -reflection_direction);

    Colord cd = o->computeColor(r.origin, p, light, false, ambient_light);
    Colord ct = RayTracer::trace(reflection, o, depth+1);

    return ct * cd;
}

RayTracer::DiffuseIntersect::DiffuseIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AIntersect(o, r, p) {}

Colord RayTracer::DiffuseIntersect::computeColor(const Light& light, const Colord& ambient_light, const int& depth) const {
    bool blocked = isBlocked(env->light.position);
    
    return o->computeColor(r.origin, p, env->light, blocked, env->ambient_light);
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