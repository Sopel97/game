#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

template <class T>
class Polygon : public Shape2<T>
{
public:
    std::vector<Vec2<T>> vertices;
    Polygon();
    Polygon(const std::initializer_list<Vec2<T>>& list);
    Polygon(const std::vector<Vec2<T>>& v);
    Polygon(std::vector<Vec2<T>>&& v);
    Polygon(Vec2<T>* v, size_t count);
    template <class X>
    Polygon(const Polygon<X>& p);
    template <class X>
    Polygon(Polygon<X>&& p);

    template <class X>
    Polygon<T>& operator=(const Polygon<X>& p);
    template <class X>
    Polygon<T>& operator=(Polygon<X> && p);

    Polygon<T> operator+(const Vec2<T>& v) const;
    Polygon<T>& operator+=(const Vec2<T>& v);
    Polygon<T> operator-(const Vec2<T>& v) const;
    Polygon<T>& operator-=(const Vec2<T>& v);

    void add(const Vec2<T>& v);
    void add(const std::vector<T>& v);
    void add(const Polygon<T>& p);
    void add(const std::initializer_list<Vec2<T>>& list);

    void translate(const Vec2<T>& v);
    void scale(const Vec2<T>& c, const Vec2<T>& s);
    void scale(const Vec2<T>& c, const T s);
    void scale(const Vec2<T>& s);
    void scale(const T s);

    Vec2<T> project(const Vec2<T>& b) const;
    std::pair<T, T> project1(const Vec2<T>& b) const;

    void transform(std::function<void(Polygon<T>&)>& func);
    void transform(std::function<void(Vec2<T>&)>& func);

    Mesh<LineSegment<T>> outline() const;

    size_t size() const;

    template <class S>
    bool intersects(const S& shape);
};

typedef Polygon<double> PolygonD;
typedef Polygon<float> PolygonF;
typedef Polygon<int> PolygonI;

#include "../src/Polygon.cpp"
#endif // POLYGON_H_INCLUDED
