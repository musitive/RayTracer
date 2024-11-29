#include "Vec.h"
#include "LightSource.h"

using namespace std;

class Material {
    public:
        bool isReflective = false;
        virtual Colori computeColor(Position from, Position p, Direction n, LightSource light, bool blocked, Colord ambient) = 0;
};