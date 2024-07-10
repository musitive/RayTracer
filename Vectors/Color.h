#pragma once

#include "Vec.h"

typedef Vec3<double> Colord;
typedef Vec3<int> Colori;

Colori bound(const Colord& v, const double min=0, const double max=1);