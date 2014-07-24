
template <class T>
Rectangle<T>::Rectangle()
{

}
template <class T>
Rectangle<T>::Rectangle(const Vec2<T>& p1, const Vec2<T>& p2)
{
    topLeft = p1;
    bottomRight = p2;
}
template <class T>
Rectangle<T>::Rectangle(const Vec2<T>& p1, const T width, const T height)
{
    topLeft = p1;
    bottomRight = p1 + Vec2<T>(width, height);
}
template <class T>
Rectangle<T>::Rectangle(const Rectangle<T>& r)
{
    topLeft = r.topLeft;
    bottomRight = r.bottomRight;
}
template <class T>
Rectangle<T>::Rectangle(Rectangle<T>&& r)
{
    topLeft = std::move(r.topLeft);
    bottomRight = std::move(r.bottomRight);
}
template <class T>
Rectangle<T>& Rectangle<T>::operator =(const Rectangle<T>& r)
{
    topLeft = r.topLeft;
    bottomRight = r.bottomRight;
    return *this;
}
template <class T>
Rectangle<T>& Rectangle<T>::operator =(Rectangle<T> && r)
{
    topLeft = std::move(r.topLeft);
    bottomRight = std::move(r.bottomRight);
    return *this;
}

template <class T>
Rectangle<T> Rectangle<T>::operator +(const Vec2<T>& v) const
{
    return Rectangle<T>(topLeft + v, bottomRight + v);
}
template <class T>
Rectangle<T>& Rectangle<T>::operator +=(const Vec2<T>& v)
{
    topLeft += v;
    bottomRight += v;
    return *this;
}
template <class T>
Rectangle<T> Rectangle<T>::operator -(const Vec2<T>& v) const
{
    return Rectangle<T>(topLeft - v, bottomRight - v);
}
template <class T>
Rectangle<T>& Rectangle<T>::operator -=(const Vec2<T>& v)
{
    topLeft -= v;
    bottomRight -= v;
    return *this;
}
template <class T>
T Rectangle<T>::width() const
{
    return bottomRight.x - topLeft.x;
}
template <class T>
T Rectangle<T>::height() const
{
    return bottomRight.y - topLeft.y;
}

template <class T>
void Rectangle<T>::translate(const Vec2<T>& v)
{

}
template <class T>
void Rectangle<T>::scale(const Vec2<T>& c, const Vec2<T>& s)
{

}
template <class T>
void Rectangle<T>::scale(const Vec2<T>& c, const T s)
{

}
template <class T>
void Rectangle<T>::scale(const Vec2<T>& s)
{

}
template <class T>
void Rectangle<T>::scale(const T s)
{

}
template <class T>
void Rectangle<T>::transform(std::function<void(Rectangle<T>&)>& func)
{
    func(*this);
}

template <class T>
Mesh<LineSegment<T>> Rectangle<T>::outline() const
{
    return Mesh<LineSegment<T>>(
    {
        LineSegment<T>(Vec2<T>(topLeft), Vec2<T>(bottomRight.x, topLeft.y)),
        LineSegment<T>(Vec2<T>(topLeft), Vec2<T>(topLeft.x, bottomRight.y)),
        LineSegment<T>(Vec2<T>(bottomRight), Vec2<T>(bottomRight.x, topLeft.y)),
        LineSegment<T>(Vec2<T>(bottomRight), Vec2<T>(topLeft.x, bottomRight.y))
    });
}
/* INTERSECTIONS */

template <class T>
template <class S>
bool Rectangle<T>::intersects(const S& b)
{
    return Intersections::intersection(*this, b);
}
