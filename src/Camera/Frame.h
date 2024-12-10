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
        ~Frame();
        void setPixel(const Point2D& setPixel, const RGBColor& color);
        RGBColor getPixel(const Point2D& getPixel) const;

    private:
        RGBColor** pixels;
};

#endif