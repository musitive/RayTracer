#include "Scene.h"
#include "Parser.h"
#include "Image.h"
#include "PPMWriter.h"

using namespace std;

int main(int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    Parser parser = Parser();
    PPMWriter ppm_writer = PPMWriter();

    Scene* scene = parser.createEnvironmentFromFile(input_filename);
    Image* image = scene->render();

    ppm_writer.writeImageToFile(image, output_filename);
    return 0;
}