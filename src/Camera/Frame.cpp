#include "Frame.h"
#include <cstdlib>
#include <fstream>

Frame::Frame(const int& w, const int& h) {
    width = w;
    height = h;
    pixels = new RGBColor*[height];

    for (int i = 0; i < height; i++) {
        pixels[i] = new RGBColor[width];
    }
}

Frame::~Frame() {
    for (int i = 0; i < height; i++) {
        delete[] pixels[i];
    }

    delete[] pixels;
}

void Frame::setPixel(const Point2D& p, const RGBColor& color) {
    pixels[p.y][p.x] = color;
}

RGBColor Frame::getPixel(const Point2D& p) const {
    return pixels[p.y][p.x];
}