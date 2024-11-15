#include <iostream>
#include <numeric>
#include <random>
#include "FileManager.h"
#include "Object.h"
#include "RayTracer.h"
#include "Environment.h"
#include "Scene.h"

using namespace std;

int main(int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    srand(time(0));

    FileManager* fm = new FileManager();
    Environment* env = fm->readFile(input_filename);
    Scene scene = Scene(env);

    scene.render(fm, output_filename);

    return 0;
}