#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include "Vec.h"

struct Point2D {
    int x, y;
};

class Frame {
    public:
        int width, height;

        Frame(const int& w, const int& h);
        void setPixel(const Point2D& setPixel, const Colord& color);
        Colord getPixel(const Point2D& getPixel) const;

    private:
        Colord** pixels;
};

#endif