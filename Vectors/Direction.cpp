#include "Direction.h"

Direction::Direction(const Position& d) {
    Position normalized_position = normalize(d);
    
    x = d.x;
    y = d.y;
    z = d.z;
}