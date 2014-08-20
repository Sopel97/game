#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

namespace Random
{
template <int I = 0> class RandomEngineT;
template <int I = 0> class CMWCEngineT;
template <int I = 0> class XorshiftEngineT;

#include "include/RandomEngine.h"
#include "include/CMWCEngine.h"
#include "include/XorshiftEngine.h"

}

#endif // RANDOM_H_INCLUDED
