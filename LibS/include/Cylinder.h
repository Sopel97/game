#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED

template <class T>
class Cylinder : public Shape<T>
{
public:
    Vec3<T> center; //cylinder base center
    T radius;
    T height;

    Cylinder();
    Cylinder(const Vec3<T>& p1, T r, T h);
    template <class X>
    Cylinder(const Cylinder<X>& c);
    template <class X>
    Cylinder(Cylinder<X>&& c);
    template <class X>
    Cylinder<T>& operator =(const Cylinder<X>& c);
    template <class X>
    Cylinder<T>& operator =(Cylinder<X> && c);

    Cylinder<T> operator +(const Vec3<T>& v) const;
    Cylinder<T>& operator +=(const Vec3<T>& v);
    Cylinder<T> operator -(const Vec3<T>& v) const;
    Cylinder<T>& operator -=(const Vec3<T>& v);
    Circle<T> base() const;

    template <class Transformation>
    void transform(Transformation&& func);

    /* INTERSECTIONS */
    template<class S>
    bool intersects(const S& b);
};

typedef Cylinder<double> CylinderD;
typedef Cylinder<float> CylinderF;
typedef Cylinder<int> CylinderI;
#include "../src/Cylinder.cpp"

#endif // CYLINDER_H_INCLUDED
