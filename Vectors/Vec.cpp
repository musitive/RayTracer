#include "Vec.h"

template <typename T>
Vec3<T>::Vec3() : x(T(0)), y(T(0)), z(T(0)) {}

template <typename T>
Vec3<T>::Vec3(T v) : x(v), y(v), z(v) {}

template <typename T>
Vec3<T>::Vec3(T u, T v, T w) : x(u), y(v), z(w) {}

template <typename T>
Vec3<T> Vec3<T>::operator + (const Vec3<T>& b) {
    return Vec3<T>(x + b.x, y + b.y, z + b.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator - (const Vec3<T>& b) {
    return Vec3<T>(x - b.x, y - b.y, z - b.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator * (const Vec3<T>& b) {
    return Vec3<T>(x * b.x, y * b.y, z * b.z);
}

template <typename T>
Vec3<T> Vec3<T>::operator * (const double& b) {
    return Vec3<T>(x * b, y * b, z * b);
}

template <typename T>
Vec3<T> Vec3<T>::operator / (const double& b) {
    return Vec3<T>(x / b, y / b, z / b);
}

template <typename T>
Vec3<T> Vec3<T>::operator - () {
    return Vec3<T>(-x, -y, -z);
}

template <typename T>
std::ostream& operator << (std::ostream &os, const Vec3<T> &v) { 
    os << v.x << ' ' << v.y << ' ' << v.z; 
    return os; 
}