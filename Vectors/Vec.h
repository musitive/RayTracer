#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

template <typename T>
class Vec3 {
    public:
        union { T x; T r; };
        union { T y; T g; };
        union { T z; T b; };

        Vec3();
        Vec3(T v);
        Vec3(T u, T v, T w);

        Vec3<T> operator + (const Vec3<T>& b);
        Vec3<T> operator - (const Vec3<T>& b);
        Vec3<T> operator * (const Vec3<T>& b);
        Vec3<T> operator * (const double& b);
        Vec3<T> operator / (const double& b);
        Vec3<T> operator - ();
        
        friend std::ostream& operator << (std::ostream& os, const Vec3<T>& v);
};