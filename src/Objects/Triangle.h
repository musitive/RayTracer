#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "AbstractObject.h"
#include "Vec.h"
#include "Ray.h"

typedef double Barycentric;

class Triangle : public AbstractObject {
    public:
        Triangle(Point3D a, Point3D b, Point3D c);
        Point3D findIntersection(const Ray& ray, const bool& culling=true) const override;
        Direction computeNormal(const Point3D& p) override;

    private:
        Point3D v1, v2, v3;
        Vector3D edge1, edge2;
        Direction normal;

        inline Barycentric computeBarycentricCoordinate(const Vector3D& a, const Vector3D& b, const double& inverse_determinant) const;
        inline bool isParallel(const float& determinant) const;
        inline bool isOutsideTriangle(const Barycentric& u) const;
        inline bool isOutsideTriangle(const Barycentric& u, const Barycentric& v) const;
};

#endif