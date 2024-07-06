#include "PPMWriter.h"

const double UMAX = 1, UMIN = -1, VMAX = -1, VMIN = 1;
const int MAX_COLOR = 255;

template<typename T>
Vec3<T> average(vector<Vec3<T>> v) {
    Vec3<T> t = Vec3<T>();
    for(Vec3<T> c: v) {
        t = t + c;
    }
    return t / v.size();
};

PPMWriter::PPMWriter() {}

void PPMWriter::writeImageToFile(Image* image, char* output_filename) {
    ofstream file;
    file.open(output_filename);
    file << "P3\n";
    file << image->width << " " << image->height << "\n";
    file << MAX_COLOR << "\n";
    for(int j = 0; j < image->height; j++) {
        for(int i = 0; i < image->width; i++) {
            Colori color = image->colors[j * image->width + i];
            file << color.x << " " << color.y << " " << color.z << "\n";
        }
    }
    file.close();
}

void PPMWriter::prepOutputFile(const string& fileName, const int& w, const int& h, const int& max_color) {
    output_file.open(fileName, ios::out);
    output_file << "P3" << endl;
    output_file << "# " << fileName << endl;
    output_file << w << ' ' << h << endl;
    output_file << max_color << endl;
}

void PPMWriter::addColor(const Colori& color) {
    output_file << color << endl;
}

void PPMWriter::closeOutput() {
    output_file.close();
}