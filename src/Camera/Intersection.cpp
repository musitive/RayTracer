#include "Intersection.h"
#include "Scene.h"
#include "RayTracer.h"

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r)
    : obj(o), ray(r), point(o->findIntersection(r)), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(point)) {}

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p)
    : obj(o), ray(r), point(p), distance(findDistanceFromPoint(r.origin)), normal(o->computeNormal(p)) {}

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance)
    : obj(o), ray(r), point(p), distance(distance), normal(o->computeNormal(p)) {}

AbstractIntersect::AbstractIntersect(AbstractObject* o, const Ray& r, const Point3D& p, const double& distance, const Direction& n)
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

MissedIntersect::MissedIntersect(AbstractObject* o, const Ray& r) : AbstractIntersect(o, r, MISS, INF, Point3D(0)) {}

Colord MissedIntersect::computeColor(const Light& light, const int& depth) const {
    return Scene::getAmbientLightColor();
}

ReflectionIntersect::ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AbstractIntersect(o, r, p) {}

Colord ReflectionIntersect::computeColor(const Light& light, const int& depth) const {
    double dt = dot(ray.direction, normal);
    Direction reflection_direction = normal * (dt * 2) - ray.direction;
    Ray reflection(point, -reflection_direction);

    Colord cd = obj->getMaterial()->computeColor(this, light, false);
    Colord ct = RayTracer::trace(reflection, obj, depth+1);

    return ct * cd;
}

DiffuseIntersect::DiffuseIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AbstractIntersect(o, r, p) {}

Colord DiffuseIntersect::computeColor(const Light& light, const int& depth) const {
    bool blocked = isBlocked(light.position);
    
    return obj->getMaterial()->computeColor(this, light, blocked);
}

bool DiffuseIntersect::isBlocked(const Point3D& light_position) const {
    Direction direction_to_light = light_position - point;
    double distance = length(light_position - point);
    Ray to_light(point, direction_to_light);

    for (AbstractObject* o: Scene::getEnvironment()->env)
        if (o != obj && o->isBlocking(to_light, light_position, distance))
            return true;

    return false;
}