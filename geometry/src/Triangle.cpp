template <class T>
Triangle<T>::Triangle()
{

}
template <class T>
Triangle<T>::Triangle(const Vec2<T>& p1, const Vec2<T>& p2, const Vec2<T>& p3)
{
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
}
template <class T>
Triangle<T>::Triangle(const Vec2<T>* p)
{
    vertices[0] = p[0];
    vertices[2] = p[2];
    vertices[1] = p[1];
}
template <class T>
Triangle<T>::Triangle(const Triangle<T>& t)
{
    vertices[0] = t.vertices[0];
    vertices[1] = t.vertices[1];
    vertices[2] = t.vertices[2];
}
template <class T>
Triangle<T>::Triangle(Triangle<T>&& t)
{
    vertices[0] = std::move(t.vertices[0]);
    vertices[1] = std::move(t.vertices[1]);
    vertices[2] = std::move(t.vertices[2]);
}
template <class T>
Triangle<T>& Triangle<T>::operator =(const Triangle<T>& t)
{
    vertices[0] = t.vertices[0];
    vertices[1] = t.vertices[1];
    vertices[2] = t.vertices[2];
    return *this;
}
template <class T>
Triangle<T>& Triangle<T>::operator =(Triangle<T> && t)
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
void Triangle<T>::transform(std::function<void(Triangle<T>&)>& func)
{
    func(*this);
}

template <class T>
Mesh<LineSegment<T>> Triangle<T>::outline() const
{
    return Mesh<LineSegment<T>>({
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
