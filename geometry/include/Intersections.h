#ifndef INTERSECTIONS_H_INCLUDED
#define INTERSECTIONS_H_INCLUDED

class Intersections
{
public:
    //2D shapes
    //Vec2
    template <class T>
    static bool intersection(const Vec2<T>& a, const Triangle<T>& b);
    template <class T>
    static bool intersection(const Vec2<T>& a, const Rectangle<T>& b);
    template <class T>
    static bool intersection(const Vec2<T>& a, const Circle<T>& b);
    template <class T>
    static bool intersection(const Vec2<T>& a, const Polygon<T>& b);
    template <class T>
    static bool intersection(const Vec2<T>& a, const Vec2<T>& b); // temporary

    //LineSegmnet
    template <class T>
    static bool intersection(const LineSegment<T>& a, const LineSegment<T>& b);
    template <class T>
    static bool intersection(const LineSegment<T>& a, const LineSegment<T>& b, Vec2<T>& intersectionPoint);
    template <class T>
    static bool intersection(const LineSegment<T>& a, const Rectangle<T>& b);

    //Rectangle
    template <class T>
    static bool intersection(const Rectangle<T>& a, const Rectangle<T>& b);
    template <class T>
    static bool intersection(const Rectangle<T>& a, const LineSegment<T>& b);
    template <class T>
    static bool intersection(const Rectangle<T>& a, const Vec2<T>& b);
    template <class T>
    static bool intersection(const Rectangle<T>& a, const Circle<T>& b);

    //Circle
    template <class T>
    static bool intersection(const Circle<T>& a, const Circle<T>& b);
    template <class T>
    static bool intersection(const Circle<T>& a, const Rectangle<T>& b);
    template <class T>
    static bool intersection(const Circle<T>& a, const Vec2<T>& b);

    //Triangle
    template <class T>
    static bool intersection(const Triangle<T>& a, const Triangle<T>& b); //need to be redone better
    template <class T>
    static bool intersection(const Triangle<T>& a, const Vec2<T>& b);

    //Polygon
    template <class T>
    static bool intersection(const Polygon<T>& a, const Vec2<T>& b);

    //3D shapes
    //Vec3

    //Cylinder
    template <class T>
    static bool intersection(const Cylinder<T>& a, const Cylinder<T>& b);

    //Cuboid
    template <class T>
    static bool intersection(const Cuboid<T>& a, const Cuboid<T>& b);


    //Meshes
    template <class T>
    static bool intersection(const Mesh<T>& a, const Mesh<T>& b);
    template <class T, class S>
    static bool intersection(const Mesh<T>& a, const S& b);
    template <class T, class S>
    static bool intersection(const S& a, const Mesh<T>& b);

    //universal
    template <class S, class T>
    static bool intersection(const S& a, const Shape2<T>* b);
    template <class S, class T>
    static bool intersection(const Shape2<T>* a, const S& b);
    template <class T>
    static bool intersection(const Shape2<T>* a, const Shape2<T>* b);



    //old
    /*
    static bool intersection(const Cuboid& a, const CuboidMesh& b);
    static bool intersection(const Triangle& a, const TriangleMesh& b); //old
    static bool intersection(const Rectangle& a, const RectangleMesh& b); //old
    static bool intersection(const Vec2& a, const TriangleMesh& b);
    static bool intersection(const RectangleMesh& a, const RectangleMesh& b);
    static bool intersection(const RectangleMesh& a, const Rectangle& b);
    static bool intersection(const CuboidMesh& a, const CuboidMesh& b);
    static bool intersection(const CuboidMesh& a, const Cuboid& b);
    static bool intersection(const TriangleMesh& a, const TriangleMesh b);
    static bool intersection(const TriangleMesh& a, const Triangle& b);
    static bool intersection(const TriangleMesh& a, const Vec2& b);
    */


private:
    Intersections() {}
};

#endif // INTERSECTIONS_H_INCLUDED
