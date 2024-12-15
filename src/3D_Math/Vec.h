#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

template<typename T>
class Vec3 {
    public:
        T x, y, z;

        Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
        Vec3(T v) : x(v), y(v), z(v) {}
        Vec3(T u, T v, T w) : x(u), y(v), z(w) {}
        Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

    const T& operator[](size_t index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw std::out_of_range("Index out of range");
    }
};

template<typename T>
bool operator == (const Vec3<T>& a, const Vec3<T>& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<typename T>
Vec3<T> operator + (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename T>
Vec3<T> operator + (const Vec3<T>& a, const double& b) {
    return Vec3<T>(a.x + b, a.y + b, a.z + b);
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& a, const double& b) {
    return Vec3<T>(a.x - b, a.y - b, a.z - b);
}

template<typename T>
Vec3<T> operator * (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<typename T>
Vec3<T> operator * (const Vec3<T>& a, const double& b) {
    return Vec3<T>(a.x * b, a.y * b, a.z * b);
}

template<typename T>
Vec3<T> operator / (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<typename T>
Vec3<T> operator / (const Vec3<T>& a, const double& b) {
    double inv_b = 1 / b;
    return a * inv_b;
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& a) {
    return Vec3<T>(-a.x, -a.y, -a.z);
}

template<typename T>
ostream & operator << (ostream &os, const Vec3<T> &v) {
    os << v.x << ' ' << v.y << ' ' << v.z; 
    return os; 
}

template<typename T>
istream & operator >> (istream &is, Vec3<T> &v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

typedef Vec3<double> RGBColor;
typedef Vec3<int> Colori;
typedef Vec3<double> Point3D;

const double MIN_COLOR = 0.0;
const double MAX_COLOR = 1.0;

class Direction : public Point3D {
    public:
        Direction(const Point3D& to, const Point3D& from);
        Direction(const Point3D& v);
};

typedef Point3D Vector3D;

template<typename T>
Vec3<T> average(vector<Vec3<T>> v) {
    Vec3<T> t = Vec3<T>();
    for(Vec3<T> c: v) {
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

template<typename T>
Vec3<T> min(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
}

template<typename T>
Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
}

const double INF = numeric_limits<double>::infinity();
const Point3D MISS = Point3D(INF);

#endif