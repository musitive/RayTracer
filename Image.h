#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include "Vec.h"

class Image {
    public:
        Image(const int& w, const int& h);

        void setPixel(const int& x, const int& y, const Colori& color);
        void writeToFile(const string& filename, const int& max_color);

    private:
        int width;
        int height;
        Colori** pixels;
};

#endif