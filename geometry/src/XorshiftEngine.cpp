template <int I>
XorshiftEngineT<I>::XorshiftEngineT(uint32_t seed) :
    RandomEngineT<I>(seed, 0xffffffff)
{
    x = seed;
    y = x + 0xb5f3c6a7; //this values are temporary, i have no idea what should it be
    z = z * 0xb5f3c6a7;
    w = w ^ 0xb5f3c6a7;
}
template <int I>
XorshiftEngineT<I>::~XorshiftEngineT()
{

}
template <int I>
uint32_t XorshiftEngineT<I>::nextRaw()
{
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19) ^ t ^ (t >> 8)) & 0xfffffffe;
}
