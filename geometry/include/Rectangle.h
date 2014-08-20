#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

template <class T>
class Rectangle : public Shape2<T>
{
public:
    Vec2<T> topLeft, bottomRight;
    Rectangle();
    Rectangle(const Vec2<T>& p1, const Vec2<T>& p2);
    Rectangle(const Vec2<T>& p1, const T width, const T height);
    template <class X>
    Rectangle(const Rectangle<X>& r);
    template <class X>
    Rectangle(Rectangle<X>&& r);
    template <class X>
    Rectangle<T>& operator =(const Rectangle<X>& r);
    template <class X>
    Rectangle<T>& operator =(Rectangle<X> && r);

    Rectangle<T> operator +(const Vec2<T>& v) const;
    Rectangle<T>& operator +=(const Vec2<T>& v);
    Rectangle<T> operator -(const Vec2<T>& v) const;
    Rectangle<T>& operator -=(const Vec2<T>& v);

    T width() const;
    T height() const;

    void translate(const Vec2<T>& v);
    void scale(const Vec2<T>& c, const Vec2<T>& s);
    void scale(const Vec2<T>& c, const T s);
    void scale(const Vec2<T>& s);
    void scale(const T s);

    void transform(std::function<void(Rectangle<T>&)>& func);

    Mesh<LineSegment<T>> outline() const;

    virtual typename Shape2<T>::ShapeID shapeId() const;

    /* INTERSECTIONS */
    template<class S>
    bool intersects(const S& b);
};

typedef Rectangle<double> RectangleD;
typedef Rectangle<float> RectangleF;
typedef Rectangle<int> RectangleI;

#include "../src/Rectangle.cpp"
#endif // RECTANGLE_H_INCLUDED
