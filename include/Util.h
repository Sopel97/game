#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "../geometry/Geometry.h"

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

    static void outputBitmapFlagsToStream(ALLEGRO_BITMAP* bitmap, std::ostream& stream = std::cout)
    {
        int bitmapFlags = al_get_bitmap_flags(bitmap);
        stream << "ALLEGRO_VIDEO_BITMAP: " << (bool)((bitmapFlags) & ALLEGRO_VIDEO_BITMAP) << '\n';
        stream << "ALLEGRO_MEMORY_BITMAP: " << (bool)((bitmapFlags) & ALLEGRO_MEMORY_BITMAP) << '\n';
        stream << "ALLEGRO_KEEP_BITMAP_FORMAT: " << (bool)((bitmapFlags) & ALLEGRO_KEEP_BITMAP_FORMAT) << '\n';
        stream << "ALLEGRO_FORCE_LOCKING: " << (bool)((bitmapFlags) & ALLEGRO_FORCE_LOCKING) << '\n';
        stream << "ALLEGRO_NO_PRESERVE_TEXTURE: " << (bool)((bitmapFlags) & ALLEGRO_NO_PRESERVE_TEXTURE) << '\n';
        stream << "ALLEGRO_ALPHA_TEST: " << (bool)((bitmapFlags) & ALLEGRO_ALPHA_TEST) << '\n';
        stream << "ALLEGRO_MIN_LINEAR: " << (bool)((bitmapFlags) & ALLEGRO_MIN_LINEAR) << '\n';
        stream << "ALLEGRO_MAG_LINEAR: " << (bool)((bitmapFlags) & ALLEGRO_MAG_LINEAR) << '\n';
        stream << "ALLEGRO_MIPMAP: " << (bool)((bitmapFlags) & ALLEGRO_MIPMAP) << '\n';
        stream << "ALLEGRO_NO_PREMULTIPLIED_ALPHA: " << (bool)((bitmapFlags) & ALLEGRO_NO_PREMULTIPLIED_ALPHA) << '\n';
    }

    static std::vector<ALLEGRO_VERTEX> constructQuadAsTriangleList(float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color)
    {
        std::vector<ALLEGRO_VERTEX> quad;
        float u2 = u1 + x2 - x1;
        float v2 = v1 + y2 - y1;
        quad.reserve(6);
        quad.push_back({x1, y1, 0, u1, v1, color});
        quad.push_back({x2, y1, 0, u2, v1, color});
        quad.push_back({x1, y2, 0, u1, v2, color});
        quad.push_back({x2, y2, 0, u2, v2, color});
        quad.push_back({x2, y1, 0, u2, v1, color});
        quad.push_back({x1, y2, 0, u1, v2, color});
        return quad;
    }
    static std::vector<ALLEGRO_VERTEX> constructQuadAsTriangleFan(float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color)
    {
        std::vector<ALLEGRO_VERTEX> quad;
        float u2 = u1 + x2 - x1;
        float v2 = v1 + y2 - y1;
        quad.reserve(4);
        quad.push_back({x1, y1, 0, u1, v1, color});
        quad.push_back({x2, y1, 0, u2, v1, color});
        quad.push_back({x2, y2, 0, u2, v2, color});
        quad.push_back({x1, y2, 0, u1, v2, color});
        return quad;
    }
    static void drawBitmap(ALLEGRO_BITMAP* bmp, float x, float y, ALLEGRO_COLOR color = al_map_rgb(255, 255, 255))
    {
        int bitmapWidth = al_get_bitmap_width(bmp);
        int bitmapHeight = al_get_bitmap_height(bmp);
        std::vector<ALLEGRO_VERTEX> bitmapQuad = Util::constructQuadAsTriangleFan(x, y, x + bitmapWidth, y + bitmapHeight, 0, 0, color);
        al_draw_prim(bitmapQuad.data(), nullptr, bmp, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
    }
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
        BitmapShifter(ALLEGRO_DISPLAY* display, int x, int y)
        {
            m_width = x;
            m_height = y;
            m_display = display;

            m_swapBuffer = al_create_bitmap(m_width, m_height);
        }
        ~BitmapShifter()
        {
            al_destroy_bitmap(m_swapBuffer);
        }
        void shift(ALLEGRO_BITMAP* bitmap, int x, int y, ALLEGRO_COLOR color)
        {
            al_set_target_bitmap(m_swapBuffer);

            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

            al_clear_to_color(color);

            //al_draw_bitmap(bitmap, x, y, 0); //this functions seems to be a problem. Did in other way.

            Util::drawBitmap(bitmap, x, y);

            al_set_target_bitmap(bitmap);
            //al_draw_bitmap(m_swapBuffer, 0, 0, 0); //this functions seems to be a problem. Did in other way.

            Util::drawBitmap(m_swapBuffer, 0, 0);

            al_set_target_bitmap(al_get_backbuffer(m_display));

            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
        }
    private:
        ALLEGRO_BITMAP* m_swapBuffer;
        int m_width;
        int m_height;
        ALLEGRO_DISPLAY* m_display;
    };

protected:
private:
    Util() {}
    virtual ~Util() {}

};

#endif // UTIL_H
