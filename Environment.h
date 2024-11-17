#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "Object.h"
#include "Camera.h"

using namespace std;

class Environment {
    public:
        Camera* cam;
        Light light;
        Colord ambient_light;
        Colord background;
        vector<Object*> env;

        Environment(Camera* cam) {
            this->cam = cam;
            light = Light();
            ambient_light = Position();
            background = Position();
            env = vector<Object*>();
        }
};

#endif