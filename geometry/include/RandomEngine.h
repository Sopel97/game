#ifndef RandomEngineT_H_INCLUDED
#define RandomEngineT_H_INCLUDED

template <int I>
class RandomEngineT
{
public:
    RandomEngineT();
    RandomEngineT(uint32_t seed, uint32_t max);
    ~RandomEngineT();
    virtual uint32_t nextRaw() = 0;

    virtual uint32_t nextInt(uint32_t rangeFirst, uint32_t rangeLast);
    virtual float nextFloat(float rangeFirst, float rangeLast);
    virtual double nextDouble(double rangeFirst, double rangeLast);

    virtual uint32_t nextInt();
    virtual float nextFloat();
    virtual double nextDouble();
    virtual bool nextBool();

    virtual uint32_t seed() const;
    virtual uint32_t max() const;
protected:
    uint32_t m_seed;
    uint32_t m_max;
};
typedef RandomEngineT<> RandomEngine;

#include "../src/RandomEngine.cpp"

#endif // RandomEngineT_H_INCLUDED
