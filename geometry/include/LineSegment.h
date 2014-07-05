#ifndef LINESEGMENT_H_INCLUDED
#define LINESEGMENT_H_INCLUDED

template <class T>
class LineSegment : public Shape2<T>
{
public:
    Vec2<T> begin;
    Vec2<T> end;
    LineSegment();
    LineSegment(const Vec2<T>& _begin, const Vec2<T>& _end);
    LineSegment(const LineSegment<T>& s);
    LineSegment(LineSegment<T>&& s);

    LineSegment<T>& operator=(const LineSegment<T>& s);
    LineSegment<T>& operator=(LineSegment<T>&& s);

    LineSegment<T> operator+(const Vec2<T>& v) const;
    LineSegment<T>& operator+=(const Vec2<T>& v);
    LineSegment<T> operator-(const Vec2<T>& v) const;
    LineSegment<T>& operator-=(const Vec2<T>& v);

    void translate(const Vec2<T>& v);
    void scale(const Vec2<T>& c, const Vec2<T>& s);
    void scale(const Vec2<T>& c, const T s);
    void scale(const Vec2<T>& s);
    void scale(const T s);

    void transform(std::function<void(LineSegment<T>&)>& func);

    Mesh<LineSegment<T>> outline() const;

    template<class S>
    bool intersects(const S& b);

    bool intersects(const LineSegment<T>& lineSegment, Vec2<T>& intersectionPoint);
};

typedef LineSegment<double> LineSegmentD;
typedef LineSegment<float> LineSegmentF;
typedef LineSegment<int> LineSegmentI;

#endif // LINESEGMENT_H_INCLUDED
