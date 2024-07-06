#pragma once
#include <iostream>
#include <fstream>
#include "Image.h"
#include "Color.h"

using namespace std;

class PPMWriter {
    private:
        ofstream output_file;

    public:
        PPMWriter();

        void writeImageToFile(Image* image, const string& output_filename);
        void prepOutputFile(const string& filename, const int& w, const int& h, const int& max_color);
        void addColor(const Colori& color);
        void closeOutput();
};