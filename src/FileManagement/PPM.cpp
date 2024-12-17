#include "PPM.h"

std::ofstream PPM::output_file = std::ofstream();

void PPM::addColor(const RGBColor& color) {
    output_file << (int) (color.x * 255) << " "
        << (int) (color.y * 255) << " "
        << (int) (color.z * 255) << " " << "\n";
}

void PPM::writeToFile(const std::string& filename, const Frame* frame) {
    output_file.open(filename);

    output_file << "P3\n";
    output_file << frame->width << " " << frame->height << "\n";
    output_file << max_color << "\n";

    addFrame(frame);

    output_file.close();
}

void PPM::addFrame(const Frame* frame) {
    RGBColor c;
    for (int i = 0; i < frame->height; i++) {
        for (int j = 0; j < frame->width; j++) {
            c = frame->getPixel({j, i});
            addColor(c);
        }
    }
}