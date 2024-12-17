#include "Direction.h"

Direction::Direction(const vec3 &from, const vec3 &to) {
    vec3 d = from - to;
    d = rt_lib::normalize(d);
    x = d.x, y = d.y, z = d.z;
}