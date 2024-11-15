#include "Scene.h"

Scene::Scene(Environment* env) {
    this->env = env;
    this->rt = new RayTracer();
}

void Scene::render(FileManager* fm, const string& output_filename) {
    const int IMAX = env->width, JMAX = env->height;

    fm->prepOutputFile(output_filename, IMAX, JMAX, 255);
    double fov = env->fov, aspectratio = IMAX / double(JMAX);
    double angle = calculateAngle(fov);
    
// TODO: Refactor this code

    for(int j = 0; j < JMAX; ++j) {
        for(int i = 0; i < IMAX; ++i) {
            Ray r = rt->computeRay(i, j, angle, aspectratio, env);
            Colori c = rt->trace(r, env, NULL, 0);
            fm->addColor(c);
        }
    }
    
    fm->closeOutput();
}