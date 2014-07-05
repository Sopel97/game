#ifndef Shape2_H_INCLUDED
#define Shape2_H_INCLUDED

template <class T>
class Shape2 : public Shape<T>
{
public:
    Shape2();

    virtual Mesh<LineSegment<T>> outline() const;

    virtual void translate(const Vec2<T>& v) = 0;
    virtual void scale(const Vec2<T>& c, const Vec2<T>& s) = 0;
    virtual void scale(const Vec2<T>& c, const T s) = 0;
    virtual void scale(const Vec2<T>& s) = 0;
    virtual void scale(const T s) = 0;

    bool intersects(const Shape2<T>& b);
    bool intersects(const Shape2<T>* b);

    virtual ~Shape2();
};

typedef Shape2<double> Shape2D;
typedef Shape2<float> Shape2F;
typedef Shape2<int> Shape2I;

#endif // Shape2_H_INCLUDED
