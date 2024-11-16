#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "Material.h"
#include "Vec.h"
#include "Ray.h"

const double INF = numeric_limits<double>::infinity();
const Position MISS = Position(INF);

class Object {
    private:
        Material* material;

    public:
        void setMaterial(Material* material);
        Material* getMaterial();

        virtual Direction computeNormal(Position p) = 0;
        virtual Position calculateIntersection(const Ray& ray, const bool& culling=true) = 0;
        virtual Colori computeColor(Position from, Position p, Light light, bool blocked, Colord ambient);
};

#endif