#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "Object.h"

using namespace std;

class Environment {
    public:
        Light light;
        Colord ambient_light;
        Colord background;
        vector<Object*> env;

        Environment();
};

#endif