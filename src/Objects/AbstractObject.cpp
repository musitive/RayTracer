#include <iostream>
#include "AbstractObject.h"
#include "Vec.h"

void AbstractObject::setMaterial(IMaterial* material) {
    this->material = material;
}

IMaterial* AbstractObject::getMaterial() const {
    return this->material;
}