#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "AbstractObject.h"
#include "Vec.h"
#include "Ray.h"

class Triangle : public AbstractObject {
    public:
        Triangle(const vec3 &a, const vec3 &b, const vec3 &c);
        vec3 findIntersection(const Ray &ray, const bool& culling=true) const override;
        Direction computeNormal(const vec3 &p) override;

    private:
        vec3 v1, v2, v3;
        vec3 edge1, edge2;
        Direction normal;

        inline double computeBarycentric(const vec3& a, const vec3& b, const double& inverse_determinant) const;
        inline bool isParallel(const float& determinant) const;
        inline bool isOutsideTriangle(const double& u) const;
        inline bool isOutsideTriangle(const double& u, const double& v) const;
};

#endif