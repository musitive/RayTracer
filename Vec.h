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

        Vec3<T> operator + (const Vec3<T>& b) const {
            return Vec3<T>(x + b.x, y + b.y, z + b.z);
        }

        Vec3<T> operator - (const Vec3<T>& b) const {
            return Vec3<T>(x - b.x, y - b.y, z - b.z);
        }

        Vec3<T> operator * (const Vec3<T>& b) const {
            return Vec3<T>(x * b.x, y * b.y, z * b.z);
        }

        Vec3<T> operator * (const double& b) const {
            return Vec3<T>(x * b, y * b, z * b);
        }

        Vec3<T> operator / (const double& b) const {
            return Vec3<T>(x / b, y / b, z / b);
        }

        Vec3<T> operator - () const {
            return Vec3<T>(-x, -y, -z);
        }

        friend ostream & operator << (ostream &os, const Vec3<T> &v) {
            os << v.x << ' ' << v.y << ' ' << v.z; 
            return os; 
        }

        friend istream & operator >> (istream &is, Vec3<T> &v) {
            is >> v.x >> v.y >> v.z;
            return is;
        }
};

typedef Vec3<double> Position;
typedef Vec3<double> Colord;
typedef Vec3<int> Colori;

double length(const Position& vec);

Position normalize(Position& vec);

class Direction : public Position {
    public:
        Direction(Position d) {
            d = normalize(d);
            x = d.x, y = d.y, z = d.z;
        }
};

class Ray {
    public:
        Position origin;        // r_0
        Direction direction;    // r_d

        Ray(Position eye, Direction s) : origin(eye), direction(s) {}
        Position findPositionOnRay(double t) {
            return origin + direction * t;
        }
};

template<typename T>
Vec3<T> average(vector<Vec3<T>> v) {
    Vec3<T> t = Vec3<T>();
    for(Vec3<T> c: v) {
        t = t + c;
    }
    return t / v.size();
};

double dot(Position& vec1, Position& vec2);

Position cross_product(Position& vec1, Position& vec2);

Colori bound(const Colord& v, const double min=0, const double max=1);

#endif