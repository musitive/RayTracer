#include <iostream>
#include "AbstractObject.h"
#include "Vec.h"

using namespace std;

void AbstractObject::setMaterial(IMaterial* material) {
    this->material = material;
}

IMaterial* AbstractObject::getMaterial() const {
    return this->material;
}

Colord AbstractObject::computeColor(Point3D from, Point3D p, Light light, bool blocked, Colord ambient) {
    Direction normal = computeNormal(p);

    return material->computeColor(from, p, normal, light, blocked, ambient);
}

bool AbstractObject::isBlocking(const Ray& to_light, const Point3D& light_position, const double& distance) {
    return length(light_position - findIntersectPosition(to_light, false)) < distance;
}