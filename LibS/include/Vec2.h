#ifndef Vec2_H_INCLUDED
#define Vec2_H_INCLUDED

template <class T>
class Vec2 : public Shape2<T>
{
public:
    T x, y;

    Vec2();
    Vec2(T _x, T _y);
    Vec2(const std::initializer_list<T>& list);
    template <class X>
    Vec2(const Vec2<X>& v);
    template <class X>
    Vec2(Vec2<X>&& v);

    template <class X>
    Vec2<T>& operator=(const Vec2<X>& v1);
    template <class X>
    Vec2<T>& operator=(Vec2<X> && v1);

    Vec2<T> operator+(const Vec2<T>& v1) const;
    Vec2<T> operator-(const Vec2<T>& v1) const;
    Vec2<T> operator*(const T scalar) const;
    Vec2<T> operator*(const Vec2<T>& v1) const;
    Vec2<T> operator/(const T scalar) const;
    Vec2<T> operator/(const Vec2<T>& v1) const;

    Vec2<T>& operator+=(const Vec2<T>& v1);
    Vec2<T>& operator-=(const Vec2<T>& v1);
    Vec2<T>& operator*=(const T scalar);
    Vec2<T>& operator*=(const Vec2<T>& v1);
    Vec2<T>& operator/=(const T scalar);
    Vec2<T>& operator/=(const Vec2<T>& v1);

    T magnitude() const;
    T distanceTo(const Vec2<T>& v1) const;
    void normalize();
    Vec2<T> normalized() const;
    Vec2<T> normalLeft() const;
    Vec2<T> normalRight() const;
    Vec2<T> normal() const; //one of above two. Should be used only when it makes no difference which one is used.
    T dot(const Vec2<T>& b) const;
    Vec2<T> project(const Vec2<T>& b) const;
    T angle() const;

    void translate(const Vec2<T>& v);
    void scale(const Vec2<T>& c, const Vec2<T>& s);
    void scale(const Vec2<T>& c, const T s);
    void scale(const Vec2<T>& s);
    void scale(const T s);

    template <class Transformation>
    void transform(Transformation&& func);

    Mesh<LineSegment<T>> outline() const;

    template<class S>
    bool intersects(const S& b);
};
typedef Vec2<double> Vec2D;
typedef Vec2<float> Vec2F;
typedef Vec2<int> Vec2I;

#include "../src/Vec2.cpp"
#endif // Vec2_H_INCLUDED
