#include "Vec.h"

Direction::Direction(const Point3D& v) {
    Point3D d = normalize(v);
    x = d.x, y = d.y, z = d.z;
}

Direction::Direction(const Point3D& from, const Point3D& to) {
    Point3D d = from - to;
    d = normalize(d);
    x = d.x, y = d.y, z = d.z;
}

double length(const Point3D& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Point3D normalize(const Point3D& vec) {
    double len = length(vec);
    if (len != 0) return vec / len;
    else return vec;
}