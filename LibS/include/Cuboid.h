#ifndef CUBOID_H_INCLUDED
#define CUBOID_H_INCLUDED

template <class T>
class Cuboid : public Shape<T>
{
public:
    Vec3<T> topLeft, bottomRight; //top has lower z
    Cuboid();
    Cuboid(const Vec3<T>& p1, const Vec3<T>& p2);
    Cuboid(const Vec3<T>& p1, const T width, const T height, const T depth);
    template <class X>
    Cuboid(const Cuboid<X>& c);
    template <class X>
    Cuboid(Cuboid<X>&& c);
    template <class X>
    Cuboid<T>& operator =(const Cuboid<X>& c);
    template <class X>
    Cuboid<T>& operator =(Cuboid<X> && c);


    Cuboid<T> operator +(const Vec3<T>& v) const;
    Cuboid<T>& operator +=(const Vec3<T>& v);
    Cuboid<T> operator -(const Vec3<T>& v) const;
    Cuboid<T>& operator -=(const Vec3<T>& v);

    T width() const;
    T height() const;
    T depth() const;

    template <class Transformation>
    void transform(Transformation&& func);

    /* INTERSECTIONS */
    template<class S>
    bool intersects(const S& b);
};

typedef Cuboid<double> CuboidD;
typedef Cuboid<float> CuboidF;
typedef Cuboid<int> CuboidI;
#include "../src/Cuboid.cpp"

#endif // CUBOID_H_INCLUDED
