#include "Vec.h"

Direction::Direction(Point3D d) {
    d = normalize(d);
    x = d.x, y = d.y, z = d.z;
}

double length(const Point3D& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Point3D normalize(Point3D& vec) {
    double l = length(vec);
    if (l != 0)
        return Point3D(vec.x / l, vec.y / l, vec.z / l);
    else
        return vec;
}