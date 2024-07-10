#pragma once
#include <vector>

#include "Camera.h"
#include "Object.h"
#include "Image.h"
#include "LightSource.h"
#include "RayTracer.h"

using namespace std;

class Scene {
    private:
        Camera* camera;
        LightSource light_source;
        Colord ambient_light;
        Colord background_color;
        vector<Object*> objects;
        RayTracer* ray_tracer;

    public:
        Scene();

        void setCamera(Camera* camera);
        void setLightSource(LightSource light_source);
        void setAmbientLight(Colord ambient_light);
        void setBackgroundColor(Colord background_color);

        void addObject(Object* object);

        Ray computeRay(double i, double j, double angle);
        Image* render();
        Colori calculateColorAtPoint(double i, double j);
};
