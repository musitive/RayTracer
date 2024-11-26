#include <iostream>
#include <numeric>
#include <random>
#include "Scene.h"
#include "Frame.h"
#include "SceneLoader.h"
#include "PPM.h"

int main(int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    srand(time(0));

    SceneLoader::loadScene(input_filename);

    Scene* scene = Scene::getInstance();
    Frame* frame = scene->render();

    PPM::writeToFile(output_filename, frame, 255);

    return 0;
}