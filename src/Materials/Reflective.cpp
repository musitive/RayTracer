#include "Reflective.h"

Reflective::Reflective(RGBColor reflective) : reflective(reflective) {
    isReflective = true;
}

RGBColor Reflective::computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) {
    return clamp(reflective, MIN_COLOR, MAX_COLOR);
}