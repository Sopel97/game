template <int I>
RandomEngineT<I>::RandomEngineT()
{

}
template <int I>
RandomEngineT<I>::~RandomEngineT()
{

}
template <int I>
RandomEngineT<I>::RandomEngineT(uint32_t seed, uint32_t max) :
    m_seed(seed),
    m_max(max)
{

}
template <int I>
uint32_t RandomEngineT<I>::nextInt(uint32_t rangeFirst, uint32_t rangeLast)
{
    return nextRaw() % (rangeLast - rangeFirst + 1) + rangeFirst;
}
template <int I>
float RandomEngineT<I>::nextFloat(float rangeFirst, float rangeLast)
{
    return nextRaw() / float(m_max) * (rangeLast - rangeFirst) + rangeFirst;
}
template <int I>
double RandomEngineT<I>::nextDouble(double rangeFirst, double rangeLast)
{
    return nextRaw() / double(m_max) * (rangeLast - rangeFirst) + rangeFirst;
}

template <int I>
uint32_t RandomEngineT<I>::nextInt()
{
    return nextRaw();
}
template <int I>
float RandomEngineT<I>::nextFloat()
{
    return nextRaw() / float(m_max);
}
template <int I>
double RandomEngineT<I>::nextDouble()
{
    return nextRaw() / double(m_max);
}
template <int I>
bool RandomEngineT<I>::nextBool()
{
    return nextRaw() > m_max / 2u;
}

template <int I>
uint32_t RandomEngineT<I>::seed() const
{
    return m_seed;
}
template <int I>
uint32_t RandomEngineT<I>::max() const
{
    return m_max;
}
