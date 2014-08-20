#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

template <class T>
class Circle : public Shape2<T>
{
public:
    Vec2<T> center;
    T radius;

    Circle();
    Circle(const Vec2<T>& p1, T r);
    template <class X>
    Circle(const Circle<X>& c);
    template <class X>
    Circle(Circle<X>&& c);
    template <class X>
    Circle& operator =(const Circle<X>& c);
    template <class X>
    Circle& operator =(Circle<X> && c);

    Circle<T> operator +(const Vec2<T>& v) const;
    Circle<T>& operator +=(const Vec2<T>& v);
    Circle<T> operator -(const Vec2<T>& v) const;
    Circle<T>& operator -=(const Vec2<T>& v);

    void translate(const Vec2<T>& v);
    void scale(const Vec2<T>& c, const Vec2<T>& s);
    void scale(const Vec2<T>& c, const T s);
    void scale(const Vec2<T>& s);
    void scale(const T s);

    void transform(std::function<void(Circle<T>&)>& func);

    Mesh<LineSegment<T>> outline() const;

    /* INTERSECTIONS */
    template<class S>
    bool intersects(const S& b);
};

typedef Circle<double> CircleD;
typedef Circle<float> CircleF;
typedef Circle<int> CircleI;
#include "../src/Circle.cpp"

#endif // CIRCLE_H_INCLUDED
