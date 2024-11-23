#include "PPM.h"

std::ofstream PPM::output_file = std::ofstream();

void PPM::addColor(const Colord& color) {
    Colori c = convert_color_to_int(color);
    output_file << c << '\n';
}

void PPM::writeToFile(const string& filename, const Frame* frame, const int& max_color) {
    output_file.open(filename);

    output_file << "P3\n";
    output_file << frame->width << " " << frame->height << "\n";
    output_file << max_color << "\n";

    addFrame(frame);

    output_file.close();
}

void PPM::addFrame(const Frame* frame) {
    Colord c;
    for (int i = 0; i < frame->height; i++) {
        for (int j = 0; j < frame->width; j++) {
            c = frame->getPixel({j, i});
            addColor(c);
        }
    }
}