#ifndef RAY_H
#define RAY_H

#include "vec3.h"
class ray {
    vec3 A, B;

   public:
    ray() {}
    ray(const vec3 &a, const vec3 &b) : A(a), B(b) {}
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + B * t; }
};

#endif /* RAY_H */
