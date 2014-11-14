template <class T>
Triangle<T>::Triangle()
{

}
template <class T>
Triangle<T>::Triangle(const Vec2<T>& p1, const Vec2<T>& p2, const Vec2<T>& p3) : vertices{p1,p2,p3}
{
}
template <class T>
Triangle<T>::Triangle(const Vec2<T>* p) : vertices{p[0],p[1],p[2]}
{
}
template <class T>
template <class X>
Triangle<T>::Triangle(const Triangle<X>& t) : vertices{t.vertices[0],t.vertices[1],t.vertices[2]}
{
}
template <class T>
template <class X>
Triangle<T>::Triangle(Triangle<X>&& t) : vertices{std::move(t.vertices[0]), std::move(t.vertices[1]), std::move(t.vertices[2])}
{
}
template <class T>
template <class X>
Triangle<T>& Triangle<T>::operator =(const Triangle<X>& t)
{
    vertices[0] = t.vertices[0];
    vertices[1] = t.vertices[1];
    vertices[2] = t.vertices[2];
    return *this;
}
template <class T>
template <class X>
Triangle<T>& Triangle<T>::operator =(Triangle<X> && t)
{
    vertices[0] = std::move(t.vertices[0]);
    vertices[1] = std::move(t.vertices[1]);
    vertices[2] = std::move(t.vertices[2]);
    return *this;
}
template <class T>
Triangle<T> Triangle<T>::operator +(const Vec2<T>& p) const
{
    return Triangle<T>(vertices[0] + p, vertices[1] + p, vertices[2] + p);
}
template <class T>
Triangle<T>& Triangle<T>::operator +=(const Vec2<T>& p)
{
    vertices[0] += p;
    vertices[1] += p;
    vertices[2] += p;
    return *this;
}
template <class T>
Triangle<T> Triangle<T>::operator -(const Vec2<T>& p) const
{
    return Triangle<T>(vertices[0] - p, vertices[1] - p, vertices[2] - p);
}
template <class T>
Triangle<T>& Triangle<T>::operator -=(const Vec2<T>& p)
{
    vertices[0] -= p;
    vertices[1] -= p;
    vertices[2] -= p;
    return *this;
}

template <class T>
void Triangle<T>::translate(const Vec2<T>& v)
{

}
template <class T>
void Triangle<T>::scale(const Vec2<T>& c, const Vec2<T>& s)
{

}
template <class T>
void Triangle<T>::scale(const Vec2<T>& c, const T s)
{

}
template <class T>
void Triangle<T>::scale(const Vec2<T>& s)
{

}
template <class T>
void Triangle<T>::scale(const T s)
{

}
template <class T>
template <class Transformation>
void Triangle<T>::transform(Transformation&& func)
{
    func(*this);
}

template <class T>
Mesh<LineSegment<T>> Triangle<T>::outline() const
{
    return Mesh<LineSegment<T>>(
    {
        LineSegment<T>(vertices[0], vertices[1]),
        LineSegment<T>(vertices[1], vertices[2]),
        LineSegment<T>(vertices[2], vertices[0])
    });
}

template <class T>
template <class S>
bool Triangle<T>::intersects(const S& b)
{
    return Intersections::intersection(*this, b);
}
