#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <vector>
#include <cmath>
#include <utility>
#include <functional>

/* Z coordinates are going down. Height is going down. So topLeft i actually 'lower' than bottomRight

                            |y
                            |
                            |
                            |
                            |
                x           |
                -------------------------->
                            |\
                            |  \z
                            |    \
                            |      \
                            |        \
                            |          \
                           \/           _|
*/
namespace
{
namespace Geo
{
/*   UTILITY   */
const double PI = 3.14159265359;

double invSqrt(double number)
{
    long long int i;
    double x2, y;
    const double threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long long int * ) &y;
    i  = 0x5fe6eb50c7b537a9LL - ( i >> 1 );
    y  = * ( double * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );
    return y;
}
double radiansToDegrees(const double radians)
{
    return radians * (180 / PI);
}
double degreesToRadians(const double degrees)
{
    return degrees / (180 / PI);
}
template<class T>
T min(const T& a, const T& b)
{
    if(a < b) return a;
    return b;
}
template<class T>
T max(const T& a, const T& b)
{
    if(a > b) return a;
    return b;
}
double clamp(int a, int mi, int ma)
{
    return max(min(a,ma),mi);
}
/*   UTILITY END  */
template <class T> class Shape;
template <class T> class Shape2;
template <class T> class Vec2;
template <class T> class Vec3;
template <class T> class Rectangle;
template <class T> class Cuboid;
template <class T> class Circle;
template <class T> class Cylinder;
template <class T> class LineSegment;
template <class T> class Triangle;
template <class T> class Polygon;
template<class T> class Mesh;

class Intersections;

/*         HEADERS         */
#include "include/Shape.h"
#include "include/Shape2.h"
#include "include/Vec2.h"
#include "include/Vec3.h"
#include "include/Rectangle.h"
#include "include/Cuboid.h"
#include "include/Circle.h"
#include "include/Cylinder.h"
#include "include/LineSegment.h"
#include "include/Triangle.h"
#include "include/Polygon.h"
#include "include/Mesh.h"

#include "include/Intersections.h"

/*         SOURCE         */
#include "src/Shape.cpp"
#include "src/Shape2.cpp"
#include "src/Vec2.cpp"
#include "src/Vec3.cpp"
#include "src/Rectangle.cpp"
#include "src/Cuboid.cpp"
#include "src/Circle.cpp"
#include "src/Cylinder.cpp"
#include "src/LineSegment.cpp"
#include "src/Triangle.cpp"
#include "src/Polygon.cpp"
#include "src/Mesh.cpp"

#include "src/Intersections.cpp"

}
}
#endif // GEOMETRY_H_INCLUDED
