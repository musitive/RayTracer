#include <iostream>
#include <numeric>
#include <random>
#include "FileManager.h"
#include "Object.h"
#include "RayTracer.h"
#include "Environment.h"

using namespace std;

int main(int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    srand(time(0));

    FileManager* fm = new FileManager();
    Environment* env = fm->readFile(input_filename);

    const int IMAX = env->width, JMAX = env->height;

    fm->prepOutputFile(output_filename, IMAX, JMAX, 255);
    double fov = env->fov, aspectratio = IMAX / double(JMAX);
    double angle = calculateAngle(fov);

    RayTracer* rt = new RayTracer();
    
// TODO: Refactor this code

    for(int j = 0; j < JMAX; ++j) {
        for(int i = 0; i < IMAX; ++i) {
            Ray r = rt->computeRay(i, j, angle, aspectratio, env);
            Colori c = rt->trace(r, env, NULL, 0);
            fm->addColor(c);
        }
    }
    
    fm->closeOutput();

    return 0;
}