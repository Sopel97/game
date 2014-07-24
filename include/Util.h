#ifndef UTIL_H
#define UTIL_H

#include <allegro5/allegro5.h>
#include "../geometry/Geometry.h"
using namespace Geo;
class Util
{
public:
    template <class T>
    static inline int fastFloor(const T& value)
    {
        int i = (int)value; /* truncate */
        return i - ( i > value ); /* convert trunc to floor */
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

            al_clear_to_color(color); //seems to not use alpha

            al_draw_bitmap(bitmap, x, y, 0);
            al_set_target_bitmap(bitmap);
            al_draw_bitmap(m_swapBuffer, 0, 0, 0);
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
