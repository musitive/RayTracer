#include <iostream>
#include "AbstractObject.h"
#include "Vec.h"

void AbstractObject::setMaterial(IMaterial* material) {
    this->material = material;
}

IMaterial* AbstractObject::getMaterial() const {
    return this->material;
}

bool AbstractObject::isBlocking(const Ray& to_light, const Point3D& light_position, const double& distance) {
    return length(light_position - findIntersection(to_light, false)) < distance;
}