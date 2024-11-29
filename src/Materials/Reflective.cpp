#include "Reflective.h"

Reflective::Reflective(Colord reflective) : reflective(reflective) {
    isReflective = true;
}

Colord Reflective::computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked) {
    return bound(reflective);
}