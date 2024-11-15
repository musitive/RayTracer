#ifndef SCENE_H
#define SCENE_H

#include "Environment.h"
#include "RayTracer.h"
#include "FileManager.h"
#include "Camera.h"

class Scene {
    public:
        Scene(Environment* env);
        void render(FileManager* fm, const string& output_filename);

    private:
        Environment* env;
        RayTracer* rt;
};

#endif