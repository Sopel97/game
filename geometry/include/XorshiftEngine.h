#ifndef XORSHIFTENGINE_H_INCLUDED
#define XORSHIFTENGINE_H_INCLUDED

template <int I>
class XorshiftEngineT : public RandomEngineT<I>
{
public:
    XorshiftEngineT(uint32_t seed = 0xb5f3c6a7);
    ~XorshiftEngineT();
    virtual uint32_t nextRaw(); /* generates 32 bit number */
protected:
    uint32_t x, y, z, w;
};
typedef XorshiftEngineT<> XorshiftEngine;

#include "../src/XorshiftEngine.cpp"

#endif // XORSHIFTENGINE_H_INCLUDED
