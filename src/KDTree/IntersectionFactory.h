#ifndef INTERSECTION_FACTORY_H
#define INTERSECTION_FACTORY_H

#include "AbstractIntersect.h"
#include "MissedIntersect.h"
#include "ReflectionIntersect.h"
#include "DiffuseIntersect.h"

/**
 * @class IntersectionFactory
 * @brief The IntersectionFactory class is a factory class that creates intersections.
 */
class IntersectionFactory {
    public:
        static AbstractIntersect* create(AbstractObject* obj, const Ray& ray, void* buffer);

        static AbstractIntersect* createMissed(void* buffer);
};

#endif