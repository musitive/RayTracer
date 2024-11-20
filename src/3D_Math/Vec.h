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
};

template<typename T>
Vec3<T> operator + (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
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
    return Vec3<T>(a.x / b, a.y / b, a.z / b);
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

typedef Vec3<double> Colord;
typedef Vec3<int> Colori;
typedef Vec3<double> Point3D;

class Direction : public Point3D {
    public:
        Direction(Point3D d);
};

template<typename T>
Vec3<T> average(vector<Vec3<T>> v) {
    Vec3<T> t = Vec3<T>();
    for(Vec3<T> c: v) {
        t = t + c;
    }
    return t / v.size();
}

double length(const Point3D& vec);
Point3D normalize(Point3D& vec);

inline double dot(const Point3D& vec1, const Point3D& vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Point3D cross_product(const Point3D& vec1, const Point3D& vec2) {
    return Point3D(vec1.y * vec2.z - vec1.z * vec2.y,
                    vec1.z * vec2.x - vec1.x * vec2.z,
                    vec1.x * vec2.y - vec1.y * vec2.x);
}

inline Colord bound(const Colord& v, const double& min = 0, const double& max = 1) {
    return Colord(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
}

inline Colori convert_color_to_int(const Colord& c) {
    return Colori(int(c.x * 255), int(c.y * 255), int(c.z * 255));
}

#endif