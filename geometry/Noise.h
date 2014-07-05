#ifndef NOISE_H_INCLUDED
#define NOISE_H_INCLUDED

#include <cmath>

namespace Noise
{
    const double PI = 3.14159265358979323846;
    const double INV_PI = 0.31830988618379067154;
template <class T>
int fastFloor( const T x )
{
    return x > 0 ? (int) x : (int) x - 1;
}

template <class T> class SimplexNoise;

#include "include/SimplexNoise.h"


#include "src/SimplexNoise.cpp"

}

#endif // NOISE_H_INCLUDED
