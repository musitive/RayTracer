#include "Frame.h"
#include <cstdlib>
#include <fstream>

Frame::Frame(const int& w, const int& h) {
    width = w;
    height = h;
    pixels = new Colord*[height];

    for (int i = 0; i < height; i++) {
        pixels[i] = new Colord[width];
    }
}

void Frame::setPixel(const Point2D& setPixel, const Colord& color) {
    pixels[setPixel.y][setPixel.x] = color;
}

void Frame::writeToFile(const string& filename, const int& max_color) {
    ofstream file;
    file.open(filename);

    file << "P3\n";
    file << width << " " << height << "\n";
    file << max_color << "\n";

    Colori color;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            color = convert_color_to_int(pixels[i][j]);
            file << color << "\n";
        }
    }

    file.close();
}