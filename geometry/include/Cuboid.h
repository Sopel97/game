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
    Cuboid(const Cuboid<T>& c);
    Cuboid(Cuboid<T>&& c);
    Cuboid<T>& operator =(const Cuboid<T>& c);
    Cuboid<T>& operator =(Cuboid<T> && c);


    Cuboid<T> operator +(const Vec3<T>& v) const;
    Cuboid<T>& operator +=(const Vec3<T>& v);
    Cuboid<T> operator -(const Vec3<T>& v) const;
    Cuboid<T>& operator -=(const Vec3<T>& v);

    T width() const;
    T height() const;
    T depth() const;

    void transform(std::function<void(Cuboid<T>&)>& func);

    /* INTERSECTIONS */
    template<class S>
    bool intersects(const S& b);
};

typedef Cuboid<double> CuboidD;
typedef Cuboid<float> CuboidF;
typedef Cuboid<int> CuboidI;
#include "../src/Cuboid.cpp"

#endif // CUBOID_H_INCLUDED
