#include "Util.h"

#include <iostream>
#include <vector>

using namespace Geo;

void Util::outputBitmapFlagsToStream(ALLEGRO_BITMAP* bitmap, std::ostream& stream)
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

std::vector<ALLEGRO_VERTEX> Util::constructQuadAsTriangleList(float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color)
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
std::vector<ALLEGRO_VERTEX> Util::constructQuadAsTriangleList(const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color)
{
    return constructQuadAsTriangleList(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, uv.x, uv.y, color);
}
void Util::appendQuadAsTriangleList(std::vector<ALLEGRO_VERTEX>& vec, float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color)
{
    float u2 = u1 + x2 - x1;
    float v2 = v1 + y2 - y1;
    vec.push_back({x1, y1, 0, u1, v1, color});
    vec.push_back({x2, y1, 0, u2, v1, color});
    vec.push_back({x1, y2, 0, u1, v2, color});
    vec.push_back({x2, y2, 0, u2, v2, color});
    vec.push_back({x2, y1, 0, u2, v1, color});
    vec.push_back({x1, y2, 0, u1, v2, color});
}
void Util::appendQuadAsTriangleList(std::vector<ALLEGRO_VERTEX>& vec, const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color)
{
    return appendQuadAsTriangleList(vec, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, uv.x, uv.y, color);
}
std::vector<ALLEGRO_VERTEX> Util::constructQuadAsTriangleFan(float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color)
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
std::vector<ALLEGRO_VERTEX> Util::constructQuadAsTriangleFan(const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color)
{
    return constructQuadAsTriangleFan(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, uv.x, uv.y, color);
}
void Util::appendQuadAsTriangleFan(std::vector<ALLEGRO_VERTEX>& vec, float x1, float y1, float x2, float y2, float u1, float v1, ALLEGRO_COLOR color)
{
    float u2 = u1 + x2 - x1;
    float v2 = v1 + y2 - y1;
    vec.push_back({x1, y1, 0, u1, v1, color});
    vec.push_back({x2, y1, 0, u2, v1, color});
    vec.push_back({x2, y2, 0, u2, v2, color});
    vec.push_back({x1, y2, 0, u1, v2, color});
}
void Util::appendQuadAsTriangleFan(std::vector<ALLEGRO_VERTEX>& vec, const Vec2F& topLeft, const Vec2F& bottomRight, const Vec2F& uv, ALLEGRO_COLOR color)
{
    return appendQuadAsTriangleFan(vec, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, uv.x, uv.y, color);
}
void Util::drawBitmap(ALLEGRO_BITMAP* bmp, float x, float y, ALLEGRO_COLOR color)
{
    int bitmapWidth = al_get_bitmap_width(bmp);
    int bitmapHeight = al_get_bitmap_height(bmp);
    std::vector<ALLEGRO_VERTEX> bitmapQuad = Util::constructQuadAsTriangleFan(x, y, x + bitmapWidth, y + bitmapHeight, 0, 0, color);
    al_draw_prim(bitmapQuad.data(), nullptr, bmp, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
}

Util::BitmapShifter::BitmapShifter(int x, int y)
{
    m_width = x;
    m_height = y;
    m_swapBuffer = al_create_bitmap(m_width, m_height);
}

Util::BitmapShifter::~BitmapShifter()
{
    al_destroy_bitmap(m_swapBuffer);
}

void Util::BitmapShifter::shift(ALLEGRO_BITMAP* bitmap, int x, int y, ALLEGRO_COLOR color)
{
    ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();
    al_set_target_bitmap(m_swapBuffer);

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

    al_clear_to_color(color);

    Util::drawBitmap(bitmap, x, y);

    al_set_target_bitmap(bitmap);

    Util::drawBitmap(m_swapBuffer, 0, 0);

    al_set_target_bitmap(oldTarget);

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}


