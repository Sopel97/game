template <class T>
Cuboid<T>::Cuboid()
{

}
template <class T>
Cuboid<T>::Cuboid(const Vec3<T>& p1, const Vec3<T>& p2)
{
    topLeft = p1;
    bottomRight = p2;
}
template <class T>
Cuboid<T>::Cuboid(const Vec3<T>& p1, const T width, const T height, const T depth)
{
    topLeft = p1;
    bottomRight = p1 + Vec3<T>(width, height, depth);
}
template <class T>
Cuboid<T>::Cuboid(const Cuboid<T>& c)
{
    topLeft = c.topLeft;
    bottomRight = c.bottomRight;
}
template <class T>
Cuboid<T>::Cuboid(Cuboid<T>&& c)
{
    topLeft = std::move(c.topLeft);
    bottomRight = std::move(c.bottomRight);
}
template <class T>
Cuboid<T>& Cuboid<T>::operator =(const Cuboid<T>& c)
{
    topLeft = c.topLeft;
    bottomRight = c.bottomRight;
    return *this;
}
template <class T>
Cuboid<T>& Cuboid<T>::operator =(Cuboid<T> && c)
{
    topLeft = std::move(c.topLeft);
    bottomRight = std::move(c.bottomRight);
    return *this;
}


template <class T>
Cuboid<T> Cuboid<T>::operator +(const Vec3<T>& v) const
{
    return Cuboid<T>(topLeft + v, bottomRight + v);
}
template <class T>
Cuboid<T>& Cuboid<T>::operator +=(const Vec3<T>& v)
{
    topLeft += v;
    bottomRight += v;
    return *this;
}
template <class T>
Cuboid<T> Cuboid<T>::operator -(const Vec3<T>& v) const
{
    return Cuboid<T>(topLeft - v, bottomRight - v);
}
template <class T>
Cuboid<T>& Cuboid<T>::operator -=(const Vec3<T>& v)
{
    topLeft -= v;
    bottomRight -= v;
    return *this;
}

template <class T>
T Cuboid<T>::width() const
{
    return bottomRight.x - topLeft.x;
}
template <class T>
T Cuboid<T>::height() const
{
    return bottomRight.y - topLeft.y;
}
template <class T>
T Cuboid<T>::depth() const
{
    return bottomRight.z - topLeft.z;
}
template <class T>
void Cuboid<T>::transform(std::function<void(Cuboid<T>&)>& func)
{
    func(*this);
}

/* INTERSECTIONS */

template <class T>
template <class S>
bool Cuboid<T>::intersects(const S& b)
{
    return Intersections::intersection(*this, b);
}
