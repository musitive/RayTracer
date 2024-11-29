#ifndef Vec_h
#define Vec_h

#include <iostream>
#include <cmath>
#include <algorithm>

template <typename T>
struct Vec3 {
    public:
        union { T x; T r; };
        union { T y; T g; };
        union { T z; T b; };

        Vec3();
        Vec3(T v);
        Vec3(T u, T v, T w);

        Vec3<T> operator+(const Vec3<T>& b) const;
        Vec3<T> operator-(const Vec3<T>& b) const;
        Vec3<T> operator*(const Vec3<T>& b) const;
        Vec3<T> operator*(const double& b) const;
        Vec3<T> operator/(const double& b) const;
        Vec3<T> operator-() const;
        Vec3<T>& operator+=(const Vec3<T>& b);
        Vec3<T>& operator-=(const Vec3<T>& b);
        Vec3<T>& operator*=(const Vec3<T>& b);
        Vec3<T>& operator*=(const double& b);
        Vec3<T>& operator/=(const double& b);
};

template <typename T>
std::istream& operator >> (std::istream& is, Vec3<T>& v);

template <typename T>
std::ostream& operator << (std::ostream& os, const Vec3<T>& v);

#endif