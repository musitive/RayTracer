#include <iostream>
#include <numeric>
#include <random>
#include "Scene.h"
#include "Frame.h"
#include "FileManager.h"

using namespace std;

int main(int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    srand(time(0));

    FileManager* fm = new FileManager();
    Scene* scene = fm->readFile(input_filename);

    Frame frame = scene->render();
    frame.writeToFile(output_filename, 255);

    return 0;
}