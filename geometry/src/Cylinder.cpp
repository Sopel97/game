template <class T>
Cylinder<T>::Cylinder()
{

}
template <class T>
Cylinder<T>::Cylinder(const Vec3<T>& p1, T r, T h)
{
    center = p1;
    radius = r;
    height = h;
}
template <class T>
Cylinder<T>::Cylinder(const Cylinder<T>& c)
{
    center = c.center;
    radius = c.radius;
    height = c.height;
}

template <class T>
Cylinder<T>& Cylinder<T>::operator =(const Cylinder<T>& c)
{
    center = c.center;
    radius = c.radius;
    height = c.height;
    return *this;
}
template <class T>
Cylinder<T>& Cylinder<T>::operator =(Cylinder<T> && c)
{
    center = std::move(c.center);
    radius = c.radius;
    height = c.height;
    return *this;
}

template <class T>
Cylinder<T> Cylinder<T>::operator +(const Vec3<T> & v) const
{
    return Cylinder<T>(center + v, radius, height);
}
template <class T>
Cylinder<T>& Cylinder<T>::operator +=(const Vec3<T> & v)
{
    center += v;
    return *this;
}
template <class T>
Cylinder<T> Cylinder<T>::operator -(const Vec3<T> & v) const
{
    return Cylinder<T>(center - v, radius, height);
}
template <class T>
Cylinder<T>& Cylinder<T>::operator -=(const Vec3<T> & v)
{
    center -= v;
    return *this;
}
template <class T>
Circle<T> Cylinder<T>::base() const
{
    return Circle<T>(Vec2<T>(center.x, center.y), radius);
}
template <class T>
void Cylinder<T>::transform(std::function<void(Cylinder<T>&)>& func)
{
    func(*this);
}

/* INTERSECTIONS */

template <class T>
template <class S>
bool Cylinder<T>::intersects(const S & b)
{
    return Intersections::intersection(*this, b);
}
