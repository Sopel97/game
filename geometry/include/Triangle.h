#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

template <class T>
class Triangle : public Shape2<T>
{
public:
    Vec2<T> vertices[3];
    Triangle();
    Triangle(const Vec2<T>& p1, const Vec2<T>& p2, const Vec2<T>& p3);
    Triangle(const Vec2<T>* p);
    Triangle(const Triangle<T>& t);
    Triangle(Triangle<T>&& t);
    Triangle<T>& operator =(const Triangle<T>& t);
    Triangle<T>& operator =(Triangle<T> && t);

    Triangle<T> operator +(const Vec2<T>& p) const;
    Triangle<T>& operator +=(const Vec2<T>& p);
    Triangle<T> operator -(const Vec2<T>& p) const;
    Triangle<T>& operator -=(const Vec2<T>& p);

    void translate(const Vec2<T>& v);
    void scale(const Vec2<T>& c, const Vec2<T>& s);
    void scale(const Vec2<T>& c, const T s);
    void scale(const Vec2<T>& s);
    void scale(const T s);

    void transform(std::function<void(Triangle<T>&)>& func);

    Mesh<LineSegment<T>> outline() const;


    template<class S>
    bool intersects(const S& b);
};

typedef Triangle<double> TriangleD;
typedef Triangle<float> TriangleF;
typedef Triangle<int> TriangleI;

#include "../src/Triangle.cpp"
#endif // TRIANGLE_H_INCLUDED
