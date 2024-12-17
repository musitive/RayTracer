#include "Reflective.h"

Reflective::Reflective(RGBColor reflective) : reflective(reflective) {}

RGBColor Reflective::computeColor(const AbstractIntersect *i, const Light &light, const bool &blocked) {
    return clamp(reflective);
}