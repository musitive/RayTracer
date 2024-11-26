#ifndef RAY_H
#define RAY_H

#include "Vec.h"

class Ray {
    public:
        Point3D origin;        // r_0
        Direction direction;    // r_d

        Ray();
        Ray(Point3D eye, Direction s);
        Point3D findPoint(double t) const;

    private:
    
};

#endif