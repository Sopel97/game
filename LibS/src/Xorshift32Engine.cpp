template <int I>
Xorshift32EngineT<I>::Xorshift32EngineT(uint32_t seed) :
    RandomEngineT<uint32_t>(seed, 0xffffffffu)
{
    x = seed;
    y = x + 0xb5f3c6a7; //this values are temporary, i have no idea what should it be
    z = z * 0xb5f3c6a7;
    w = w ^ 0xb5f3c6a7;
}
template <int I>
Xorshift32EngineT<I>::~Xorshift32EngineT()
{

}
template <int I>
uint32_t Xorshift32EngineT<I>::nextRaw()
{
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}
