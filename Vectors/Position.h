#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

#include "Vec.h"

using namespace std;

typedef Vec3<double> Position;

double length(const Position& vec);
Position normalize(const Position& vec);
double dot(Position& vec1, Position& vec2);
Position cross_product(Position& vec1, Position& vec2);