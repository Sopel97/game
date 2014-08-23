#include "../include/Intersections.h"
template <class T>
Vec2<T>::Vec2()
{
    x = y = 0;
}

template <class T>
Vec2<T>::Vec2(T _x, T _y)
{
    x = _x;
    y = _y;
}
template <class T>
Vec2<T>::Vec2(const std::initializer_list<T>& list)
{
    typename std::initializer_list<T>::iterator it = list.begin();
    x = *it;
    ++it;
    y = *it;
}
template <class T>
template <class O>
Vec2<T>::Vec2(const Vec2<O>& v)
{
    x = v.x;
    y = v.y;
}
template <class T>
Vec2<T>::Vec2(const Vec2<T>& v)
{
    x = v.x;
    y = v.y;
}
template <class T>
Vec2<T>::Vec2(Vec2<T>&& v)
{
    x = v.x;
    y = v.y;
}
template <class T>
Vec2<T>& Vec2<T>::operator=(const Vec2<T>& v1)
{
    x = v1.x;
    y = v1.y;
    return *this;
}
template <class T>
Vec2<T>& Vec2<T>::operator=(Vec2<T> && v1)
{
    x = v1.x;
    y = v1.y;
    return *this;
}

template <class T>
Vec2<T> Vec2<T>::operator+(const Vec2& v1) const
{
    return Vec2<T>(x + v1.x, y + v1.y);
}
template <class T>
Vec2<T> Vec2<T>::operator-(const Vec2& v1) const
{
    return Vec2<T>(x - v1.x, y - v1.y);
}
template <class T>
Vec2<T> Vec2<T>::operator*(const T scalar) const
{
    return Vec2<T>(x * scalar, y * scalar);
}
template <class T>
Vec2<T> Vec2<T>::operator*(const Vec2& v1) const
{
    return Vec2<T>(x * v1.x, y * v1.y);
}
template <class T>
Vec2<T> Vec2<T>::operator/(const T scalar) const
{
    return Vec2<T>(x / scalar, y / scalar);
}
template <class T>
Vec2<T> Vec2<T>::operator/(const Vec2& v1) const
{
    return Vec2<T>(x / v1.x, y / v1.y);
}

template <class T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& v1)
{
    x += v1.x;
    y += v1.y;
    return *this;
}
template <class T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& v1)
{
    x -= v1.x;
    y -= v1.y;
    return *this;
}
template <class T>
Vec2<T>& Vec2<T>::operator*=(const T scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
template <class T>
Vec2<T>& Vec2<T>::operator*=(const Vec2& v1)
{
    x *= v1.x;
    y *= v1.y;
    return *this;
}
template <class T>
Vec2<T>& Vec2<T>::operator/=(const T scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}
template <class T>
Vec2<T>& Vec2<T>::operator/=(const Vec2& v1)
{
    x /= v1.x;
    y /= v1.y;
    return *this;
}


template <class T>
T Vec2<T>::magnitude() const
{
    return 1. / invSqrt(x * x + y * y);
}
template <class T>
T Vec2<T>::distanceTo(const Vec2& v1) const
{
    T dx = x - v1.x;
    T dy = y - v1.y;
    return 1. / (invSqrt(dx * dx + dy * dy));
}
template <class T>
void Vec2<T>::normalize()
{
    T invertedSquareRoot = invSqrt(x * x + y * y);
    x *= invertedSquareRoot;
    y *= invertedSquareRoot;
}
template <class T>
Vec2<T> Vec2<T>::normal() const
{
    T invertedSquareRoot = invSqrt(x * x + y * y);
    return Vec2<T>(x * invertedSquareRoot, y * invertedSquareRoot);
}
template <class T>
T Vec2<T>::angle() const
{
    return radiansToDegrees(atan2(x, y));
}

template <class T>
void Vec2<T>::translate(const Vec2<T>& v)
{

}
template <class T>
void Vec2<T>::scale(const Vec2<T>& c, const Vec2<T>& s)
{

}
template <class T>
void Vec2<T>::scale(const Vec2<T>& c, const T s)
{

}
template <class T>
void Vec2<T>::scale(const Vec2<T>& s)
{

}
template <class T>
void Vec2<T>::scale(const T s)
{

}
template <class T>
void Vec2<T>::transform(std::function<void(Vec2<T>&)>& func)
{
    func(*this);
}

template <class T>
Mesh<LineSegment<T>> Vec2<T>::outline() const
{
    return Mesh<LineSegment<T>>();
}
template <class T>
template <class S>
bool Vec2<T>::intersects(const S& b)
{
    return Intersections::intersection(*this, b);
}
