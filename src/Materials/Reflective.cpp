#include "Reflective.h"

Reflective::Reflective(Colord reflective) : reflective(reflective) {
    isReflective = true;
}

Colord Reflective::computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) {
    return clamp(reflective, MIN_COLOR, MAX_COLOR);
}