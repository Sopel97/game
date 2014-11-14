#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include "../LibS/Geometry.h"

using namespace Geo;

class Util
{
public:
    template <class T>
    static inline int fastFloor(const T& value)
    {
        int i = (int)value; /* truncate */
        return i - ( value < 0.0 ); /* convert trunc to floor */
    }
    template <class T>
    static inline Vec2I fastFloor(const Vec2<T>& value)
    {
        return Vec2I(fastFloor(value.x), fastFloor(value.y));
    }
    template <class T>
    static inline int mod(const T& value, const T& div)
    {
        int r = value % div;
        if(r < 0) r += div;
        return r;
    }
    template <class T>
    static inline float mod(const float value, const T& div)
    {
        float r = fmod(value, div);
        if(r < 0) r += div;
        return r;
    }

    template <class T>
    class Range
    {
    public:
        T min, max;

        Range(T& _min, T& _max) : min(_min), max(_max)
        {

        }
        Range() : min(0), max(0)
        {

        }
    };
    typedef Range<float> RangeF;
    typedef Range<double> RangeD;
    typedef Range<int> RangeI;

    template <class It>
    class IteratorRange
    {
    public:
        IteratorRange(const It& begin, const It& end) : m_begin(begin), m_end(end)
        {

        }
        const It& begin() const
        {
            return m_begin;
        }
        const It& end() const
        {
            return m_end;
        }
        It begin()
        {
            return m_begin;
        }
        It end()
        {
            return m_end;
        }
    private:
        It m_begin;
        It m_end;
    };

protected:
private:
    Util() {}
    virtual ~Util() {}

};

#endif // UTIL_H
