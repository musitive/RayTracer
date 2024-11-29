#include "Color.h"

Colori bound(const Colord& v, const double min, const double max) {
    return Colori(clamp(v.x, min, max)*255, clamp(v.y, min, max)*255, clamp(v.z, min, max)*255);
}