#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "AbstractObject.h"

using namespace std;

class Environment {
    public:
        Light light;
        Colord ambient_light;
        Colord background;
        vector<AbstractObject*> env;

        Environment();
};

#endif