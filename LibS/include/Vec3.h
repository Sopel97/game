#ifndef Vec3_H_INCLUDED
#define Vec3_H_INCLUDED

template <class T>
class Vec3 : public Shape<T>
{
public:
    T x, y, z;

    Vec3();
    Vec3(T _x, T _y, T _z);
    Vec3(const std::initializer_list<T>& list);
    template <class X>
    Vec3(const Vec3<X>& v);
    template <class X>
    Vec3(Vec3<X>&& v);

    template <class X>
    Vec3<T>& operator=(const Vec3<X>& v1);
    template <class X>
    Vec3<T>& operator=(Vec3<X> && v1);

    Vec3<T> operator+(const Vec3<T>& v1) const;
    Vec3<T> operator-(const Vec3<T>& v1) const;
    Vec3<T> operator*(const T scalar) const;
    Vec3<T> operator*(const Vec3<T>& v1) const;
    Vec3<T> operator/(const T scalar) const;

    Vec3<T>& operator+=(const Vec3<T>& v1);
    Vec3<T>& operator-=(const Vec3<T>& v1);
    Vec3<T>& operator*=(const T scalar);
    Vec3<T>& operator*=(const Vec3<T>& v1);
    Vec3<T>& operator/=(const T scalar);

    T magnitude();
    T distanceTo(const Vec3<T>& v);
    void normalize();
    Vec3<T> normal();
    T angle() const;

    template <class Transformation>
    void transform(Transformation&& func);

    template<class S>
    bool intersects(const S& b);
};

typedef Vec3<double> Vec3D;
typedef Vec3<float> Vec3F;
typedef Vec3<int> Vec3I;

#include "../src/Vec3.cpp"
#endif // Vec3_H_INCLUDED
