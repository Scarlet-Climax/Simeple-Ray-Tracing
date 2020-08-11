#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>

#include "random.h"
using namespace std;

class vec3 {
    float e[3];

   public:
    vec3() {}
    vec3(float e0, float e1, float e2) { e[0] = e0, e[1] = e1, e[2] = e2; }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3& v2) {
        e[0] += v2[0];
        e[1] += v2[1];
        e[2] += v2[2];
        return *this;
    }
    inline vec3& operator-=(const vec3& v2) {
        e[0] -= v2[0];
        e[1] -= v2[1];
        e[2] -= v2[2];
        return *this;
    }
    inline vec3& operator*=(const vec3& v2) {
        e[0] *= v2[0];
        e[1] *= v2[1];
        e[2] *= v2[2];
        return *this;
    }
    inline vec3& operator/=(const vec3& v2) {
        e[0] /= v2[0];
        e[1] /= v2[1];
        e[2] /= v2[2];
        return *this;
    }
    inline vec3& operator*=(const float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    inline vec3& operator/=(const float t) {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    }

    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void make_unit_vector() {
        float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }
};
inline istream& operator>>(istream& is, vec3& t) {
    is >> t[0] >> t[1] >> t[2];
    return is;
}
inline ostream& operator<<(ostream& ou, const vec3& t) {
    ou << t[0] << ' ' << t[1] << ' ' << t[2];
    return ou;
}
inline vec3 operator+(const vec3& v1, const vec3& v2) {
    return vec3{v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]};
}
inline vec3 operator-(const vec3& v1, const vec3& v2) {
    return vec3{v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]};
}
inline vec3 operator*(const vec3& v1, const vec3& v2) {
    return vec3{v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]};
}
inline vec3 operator/(const vec3& v1, const vec3& v2) {
    return vec3{v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]};
}
inline vec3 operator*(const vec3& v1, const float& t) {
    return vec3{v1[0] * t, v1[1] * t, v1[2] * t};
}
inline vec3 operator*(const float& t, const vec3& v1) {
    return vec3{v1[0] * t, v1[1] * t, v1[2] * t};
}
inline vec3 operator/(const vec3& v1, const float& t) {
    return vec3{v1[0] / t, v1[1] / t, v1[2] / t};
}
inline float dot(const vec3& v1, const vec3& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3{v1[1] * v2[2] - v1[2] * v2[1],
                v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]};
}
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(random_float(), random_float(), random_float()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1);
    return p;
}

inline vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0 * vec3(random_float(), random_float(), 0) - vec3(1, 1, 0);
    } while (p.squared_length() >= 1);
    return p;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}
inline bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    return false;
}

#endif /* VEC3_H */
