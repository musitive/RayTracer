#include "Intersection.h"

Intersection::Intersection() {
    o = NULL;
    p = Point3D();
    r = Ray();
    distance = numeric_limits<double>::infinity();
}

Intersection::Intersection(Object* o, const Ray& r) {
    this->o = o;
    this->p = o->findIntersectPosition(r);
    this->r = r;
    distance = findDistanceFromPoint(r.origin);
}

double Intersection::findDistanceFromPoint(Point3D p) const {
    return length(this->p - p);
}

bool Intersection::isCloserThan(const Intersection& i) const {
    return distance < i.getDistance();
}

Direction Intersection::computeNormal() const {
    return o->computeNormal(p);
}

Colord Intersection::computeColor(const Light& light, const bool& blocked, const Colord& ambient_light) const {
    return o->computeColor(r.origin, p, light, blocked, ambient_light);
}

double Intersection::getDistance() const {
    return distance;
}

Object* Intersection::getObject() const {
    return o;
}

Ray Intersection::getRay() const {
    return r;
}

Point3D Intersection::getPosition() const {
    return p;
}