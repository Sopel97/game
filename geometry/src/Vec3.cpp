template <class T>
Vec3<T>::Vec3()
{
    x = y = z = 0.0;
}
template <class T>
Vec3<T>::Vec3(T _x, T _y, T _z)
{
    x = _x;
    y = _y;
    z = _z;
}
template <class T>
Vec3<T>::Vec3(const std::initializer_list<T>& list)
{
    typename std::initializer_list<T>::iterator it = list.begin();
    x = *it;
    ++it;
    y = *it;
    ++it;
    z = *it;
}
template <class T>
Vec3<T>::Vec3(const Vec3<T>& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}
template <class T>
Vec3<T>::Vec3(Vec3<T>&& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

template <class T>
Vec3<T>& Vec3<T>::operator=(const Vec3<T>& v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;
    return *this;
}
template <class T>
Vec3<T>& Vec3<T>::operator=(Vec3<T> && v1)
{
    x = v1.x;
    y = v1.y;
    z = v1.z;
    return *this;
}
template <class T>
Vec3<T> Vec3<T>::operator+(const Vec3<T>& v1) const
{
    return Vec3<T>(x + v1.x, y + v1.y, z + v1.z);
}
template <class T>
Vec3<T> Vec3<T>::operator-(const Vec3<T>& v1) const
{
    return Vec3<T>(x - v1.x, y - v1.y, z - v1.z);
}
template <class T>
Vec3<T> Vec3<T>::operator*(const T scalar) const
{
    return Vec3<T>(x * scalar, y * scalar, z * scalar);
}
template <class T>
Vec3<T> Vec3<T>::operator*(const Vec3<T>& v1) const
{
    return Vec3<T>(x * v1.x, y * v1.y, z * v1.z);
}
template <class T>
Vec3<T> Vec3<T>::operator/(const T scalar) const
{
    return Vec3<T>(x / scalar, y / scalar, z / scalar);
}

template <class T>
Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v1)
{
    x += v1.x;
    y += v1.y;
    z += v1.z;
    return *this;
}
template <class T>
Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v1)
{
    x -= v1.x;
    y -= v1.y;
    z -= v1.z;
    return *this;
}
template <class T>
Vec3<T>& Vec3<T>::operator*=(const T scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}
template <class T>
Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& v1)
{
    x *= v1.x;
    y *= v1.y;
    z *= v1.z;
    return *this;
}
template <class T>
Vec3<T>& Vec3<T>::operator/=(const T scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

template <class T>
T Vec3<T>::magnitude()
{
    return 1. / invSqrt((x * x) + (y * y) + (z * z));
}
template <class T>
T Vec3<T>::distanceTo(const Vec3<T>& v)
{
    T dx = x - v.x;
    T dy = y - v.y;
    T dz = z - v.z;
    return 1. / invSqrt(dx * dx + dy * dy + dz * dz);
}
template <class T>
void Vec3<T>::normalize()
{
    T invertedSquareRoot = invSqrt(x * x + y * y + z * z);
    x *= invertedSquareRoot;
    y *= invertedSquareRoot;
    z *= invertedSquareRoot;
}
template <class T>
Vec3<T> Vec3<T>::normal()
{
    T invertedSquareRoot = invSqrt(x * x + y * y + z * z);
    return Vec3<T>(x * invertedSquareRoot, y * invertedSquareRoot, z * invertedSquareRoot);
}
template <class T>
T Vec3<T>::angle() const
{
    return 0.0; //currently blank
}
template <class T>
void Vec3<T>::transform(std::function<void(Vec3<T>&)>& func)
{
    func(*this);
}
template <class T>
template <class S>
bool Vec3<T>::intersects(const S& b)
{
    return Intersections::intersection(*this, b);
}
