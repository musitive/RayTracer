#ifndef SCENE_H
#define SCENE_H

#include "Environment.h"
#include "RayTracer.h"
#include "Camera.h"

class Scene {
    public:
        Scene(Environment* env, Camera* cam);
        Frame render();
        int getCameraWidth() const;
        int getCameraHeight() const;

    private:
        Environment* env;
        Camera* cam;
};

#endif