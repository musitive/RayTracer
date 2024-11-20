#include <iostream>
#include "Object.h"
#include "Vec.h"

using namespace std;

void Object::setMaterial(IMaterial* material) {
    this->material = material;
}

IMaterial* Object::getMaterial() {
    return this->material;
}

Colord Object::computeColor(Point3D from, Point3D p, Light light, bool blocked, Colord ambient) {
    Direction normal = computeNormal(p);

    return material->computeColor(from, p, normal, light, blocked, ambient);
}

bool Object::isBlocking(const Ray& to_light, const Point3D& light_position, const double& distance) {
    return length(light_position - findIntersectPosition(to_light, false)) < distance;
}