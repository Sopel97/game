template <int I>
CMWCEngineT<I>::CMWCEngineT(uint32_t seed) :
    RandomEngine(seed, 0x00010000U)
{
    c = 362436;

    Q[0] = seed;
    Q[1] = seed + PHI;
    Q[2] = seed + PHI + PHI;

    for (int i = 3; i < 4096; i++)
        Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}
template <int I>
CMWCEngineT<I>::~CMWCEngineT()
{

}
template <int I>
uint32_t CMWCEngineT<I>::nextRaw()
{
    static uint32_t i = 4095;
    uint64_t t;

    i = (i + 1) & 4095;
    t = (18705ULL * Q[i]) + c;
    c = t >> 32;
    Q[i] = 0xfffffffe - t;

    return Q[i] & 0x0000FFFFU;
}
