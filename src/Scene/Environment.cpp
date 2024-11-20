#include "Environment.h"

Environment::Environment()  {
    light = Light();
    ambient_light = Point3D();
    background = Point3D();
    env = vector<AbstractObject*>();
}