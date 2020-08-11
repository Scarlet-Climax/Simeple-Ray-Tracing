#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
using namespace std;
inline float random_float() {
    return rand() / (RAND_MAX + 1.0);
}

#endif /* RANDOM_H */
