#include "Vec.h"
#include "Object.h"
#include <numeric>
#include <random>

using namespace std;

class RayTracer {
    private:
        const int MAX_DEPTH = 4;
    public:
        RayTracer();

        virtual Colori trace(Ray ray, Scene* env, Object* current, const int& depth);
        Object* findClosestIntersection(Ray ray, vector<Object*>* objects, Object* origin_object);
};