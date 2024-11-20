#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include "Vec.h"

struct Point2D {
    int x, y;
};

class Frame {
    public:
        Frame(const int& w, const int& h);

        void setPixel(const Point2D& setPixel, const Colord& color);
        void writeToFile(const string& filename, const int& max_color);

    private:
        int width, height;
        Colord** pixels;
};

#endif