#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

template<typename double>
class vec3 {
    public:
        double x, y, z;

        vec3() : x(double(0)), y(double(0)), z(double(0)) {}
        vec3(double v) : x(v), y(v), z(v) {}
        vec3(double u, double v, double w) : x(u), y(v), z(w) {}
        vec3(const vec3<double>& v) : x(v.x), y(v.y), z(v.z) {}

    const double& operator[](size_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range");
    }
};

template<typename double>
bool operator == (const vec3<double>& a, const vec3<double>& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<typename double>
vec3<double> operator + (const vec3<double>& a, const vec3<double>& b) {
    return vec3<double>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename double>
vec3<double> operator + (const vec3<double>& a, const double& b) {
    return vec3<double>(a.x + b, a.y + b, a.z + b);
}

template<typename double>
vec3<double> operator - (const vec3<double>& a, const vec3<double>& b) {
    return vec3<double>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename double>
vec3<double> operator - (const vec3<double>& a, const double& b) {
    return vec3<double>(a.x - b, a.y - b, a.z - b);
}

template<typename double>
vec3<double> operator * (const vec3<double>& a, const vec3<double>& b) {
    return vec3<double>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<typename double>
vec3<double> operator * (const vec3<double>& a, const double& b) {
    return vec3<double>(a.x * b, a.y * b, a.z * b);
}

template<typename double>
vec3<double> operator / (const vec3<double>& a, const vec3<double>& b) {
    return vec3<double>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<typename double>
vec3<double> operator / (const vec3<double>& a, const double& b) {
    double inv_b = 1 / b;
    return a * inv_b;
}

template<typename double>
vec3<double> operator - (const vec3<double>& a) {
    return vec3<double>(-a.x, -a.y, -a.z);
}

template<typename double>
ostream & operator << (ostream &os, const vec3<double> &v) {
    os << v.x << ' ' << v.y << ' ' << v.z; 
    return os; 
}

template<typename double>
istream & operator >> (istream &is, vec3<double> &v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

typedef vec3<double> RGBColor;
typedef vec3<int> Colori;
typedef vec3<double> Point3D;

const double MIN_COLOR = 0.0;
const double MAX_COLOR = 1.0;

class Direction : public Point3D {
    public:
        Direction(const Point3D& to, const Point3D& from);
        Direction(const Point3D& v);
};

typedef Point3D Vector3D;

template<typename double>
vec3<double> average(vector<vec3<double>> v) {
    vec3<double> t = vec3<double>();
    for(vec3<double> c: v) {
        t = t + c;
    }
    return t / v.size();
}

double length(const Point3D& vec);
Point3D normalize(const Point3D& vec);

inline double dot(const Point3D& vec1, const Point3D& vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Point3D cross_product(const Point3D& vec1, const Point3D& vec2) {
    return Point3D(vec1.y * vec2.z - vec1.z * vec2.y,
                    vec1.z * vec2.x - vec1.x * vec2.z,
                    vec1.x * vec2.y - vec1.y * vec2.x);
}

inline RGBColor clamp(const RGBColor& v, const double& min, const double& max) {
    return RGBColor(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
}

inline Colori convert_color_to_int(const RGBColor& c) {
    return Colori(int(c.x * 255), int(c.y * 255), int(c.z * 255));
}

inline double square(const double& x) {
    return x * x;
}

inline double square(const Vector3D& a) {
    return dot(a, a);
}

template<typename double>
vec3<double> min(const vec3<double>& a, const vec3<double>& b) {
    return vec3<double>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
}

template<typename double>
vec3<double> max(const vec3<double>& a, const vec3<double>& b) {
    return vec3<double>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
}

const double INF = numeric_limits<double>::infinity();
const Point3D MISS = Point3D(INF);

#endif