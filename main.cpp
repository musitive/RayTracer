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
    
    for(int j = 0; j < JMAX; ++j) {
        for(int i = 0; i < IMAX; ++i) {
            vector<Colori> colors = rt->subdivide(i, j, 4, angle, aspectratio, env);
            fm->addColor(average(colors));
        }
    }
    
    fm->closeOutput();

    return 0;
}