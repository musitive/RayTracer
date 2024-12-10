#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <fstream>

#include "Vec.h"
#include "Frame.h"

class PPM {
    public:
        static void writeToFile(const string& filename, const Frame* frame);

    private:
        const static int max_color = 255;
        static std::ofstream output_file;
        static inline void addColor(const RGBColor& color);
        static void addFrame(const Frame* frame);
};

#endif