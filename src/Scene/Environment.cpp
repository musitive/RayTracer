#include "Environment.h"

Environment::Environment()  {
    light = Light();
    ambient_light = Point3D();
    background = Point3D();
    env = vector<AbstractObject*>();
}

Environment::~Environment() {
    for (AbstractObject* o : env) {
        delete o;
    }
}