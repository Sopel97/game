#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include "../geometry/Geometry.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

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

    static void outputBitmapFlagsToStream(ALLEGRO_BITMAP* bitmap, std::ostream& stream = std::cout);

    static std::vector<ALLEGRO_VERTEX> constructQuadAsTriangleList(float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color);
    static std::vector<ALLEGRO_VERTEX> constructQuadAsTriangleList(const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color);

    static void appendQuadAsTriangleList(std::vector<ALLEGRO_VERTEX>& vec, float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color);
    static void appendQuadAsTriangleList(std::vector<ALLEGRO_VERTEX>& vec, const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color);

    static std::vector<ALLEGRO_VERTEX> constructQuadAsTriangleFan(float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color);
    static std::vector<ALLEGRO_VERTEX> constructQuadAsTriangleFan(const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color);

    static void appendQuadAsTriangleFan(std::vector<ALLEGRO_VERTEX>& vec, float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color);
    static void appendQuadAsTriangleFan(std::vector<ALLEGRO_VERTEX>& vec, const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color);

    static void drawBitmap(ALLEGRO_BITMAP* bmp, float x, float y, ALLEGRO_COLOR color = al_map_rgb(255, 255, 255));

    template <class T>
    class Range
    {
    public:
        T min, max;

        Range(T& _min, T& _max)
        {
            min = _min;
            max = _max;
        }
        Range()
        {

        }
    };
    typedef Range<float> RangeF;
    typedef Range<double> RangeD;
    typedef Range<int> RangeI;

    class BitmapShifter
    {
    public:
        BitmapShifter(int x, int y);
        ~BitmapShifter();
        void shift(ALLEGRO_BITMAP* bitmap, int x, int y, ALLEGRO_COLOR color);
    private:
        ALLEGRO_BITMAP* m_swapBuffer;
        int m_width;
        int m_height;
    };

protected:
private:
    Util() {}
    virtual ~Util() {}

};

#endif // UTIL_H
