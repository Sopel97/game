template <class T>
Polygon<T>::Polygon()
{

}
template <class T>
Polygon<T>::Polygon(const std::initializer_list<Vec2<T>>& list)
{
    vertices.assign(list);
}
template <class T>
Polygon<T>::Polygon(const std::vector<Vec2<T>>& v)
{
    vertices = v;
}
template <class T>
Polygon<T>::Polygon(std::vector<Vec2<T>>&& v)
{
    vertices = std::move(v);
}
template <class T>
Polygon<T>::Polygon(Vec2<T>* v, size_t count)
{
    vertices.assign(v, v + count);
}
template <class T>
template <class X>
Polygon<T>::Polygon(const Polygon<X>& p)
{
    vertices = p.vertices;
}
template <class T>
template <class X>
Polygon<T>::Polygon(Polygon<X>&& p)
{
    vertices = std::move(p.vertices);
}

template <class T>
template <class X>
Polygon<T>& Polygon<T>::operator=(const Polygon<X>& p)
{
    vertices = p.vertices;
    return *this;
}
template <class T>
template <class X>
Polygon<T>& Polygon<T>::operator=(Polygon<X> && p)
{
    vertices = std::move(p.vertices);
    return *this;
}

template <class T>
Polygon<T> Polygon<T>::operator+(const Vec2<T>& v) const
{
    Polygon newPolygon(*this);
    newPolygon += v;
    return newPolygon;
}
template <class T>
Polygon<T>& Polygon<T>::operator+=(const Vec2<T>& v)
{
    for(Vec2<T>& vertex : vertices)
    {
        vertex += v;
    }
    return *this;
}
template <class T>
Polygon<T> Polygon<T>::operator-(const Vec2<T>& v) const
{
    Polygon newPolygon(*this);
    newPolygon -= v;
    return newPolygon;
}
template <class T>
Polygon<T>& Polygon<T>::operator-=(const Vec2<T>& v)
{
    for(Vec2<T>& vertex : vertices)
    {
        vertex -= v;
    }
    return *this;
}

template <class T>
void Polygon<T>::add(const Vec2<T>& v)
{
    vertices.push_back(v);
}
template <class T>
void Polygon<T>::add(const std::vector<T>& v)
{
    vertices.insert(vertices.end(), v.begin(), v.end());
}
template <class T>
void Polygon<T>::add(const Polygon<T>& p)
{
    add(p.vertices);
}
template <class T>
void Polygon<T>::add(const std::initializer_list<Vec2<T>>& list)
{
    vertices.insert(vertices.end(), list.begin(), list.end());
}

template <class T>
void Polygon<T>::translate(const Vec2<T>& v)
{

}
template <class T>
void Polygon<T>::scale(const Vec2<T>& c, const Vec2<T>& s)
{

}
template <class T>
void Polygon<T>::scale(const Vec2<T>& c, const T s)
{

}
template <class T>
void Polygon<T>::scale(const Vec2<T>& s)
{

}
template <class T>
void Polygon<T>::scale(const T s)
{

}
template <class T>
void Polygon<T>::transform(std::function<void(Polygon<T>&)>& func)
{
    func(*this);
}
template <class T>
void Polygon<T>::transform(std::function<void(Vec2<T>&)>& func)
{
    for(Vec2<T>& vertex : vertices)
    {
        func(vertex);
    }
}

template <class T>
Vec2<T> Polygon<T>::project(const Vec2<T>& b) const
{
    Vec2<T> projection;

    return projection;
}

template <class T>
std::pair<T, T> Polygon<T>::project1(const Vec2<T>& b) const
{
    T minProjection;
    T maxProjection;
    minProjection = maxProjection = vertices[0].dot(b);
    for(const Vec2<T>& vertex : vertices)
    {
        T dotProduct = vertex.dot(b);
        if(dotProduct < minProjection) minProjection = dotProduct;
        else if(dotProduct > maxProjection) maxProjection = dotProduct;
    }
    return std::pair<T,T>(minProjection, maxProjection);
}
template <class T>
Mesh<LineSegment<T>> Polygon<T>::outline() const
{
    Mesh<LineSegment<T>> outline;
    int vertexCount = vertices.size() - 1;
    for(int i = 0; i < vertexCount; ++i)
    {
        outline.add(LineSegment<T>({vertices[i]}, {vertices[i + 1]}));
    }
    outline.add(LineSegment<T>(vertices[vertexCount], vertices[0]));
    return outline;
}

template <class T>
size_t Polygon<T>::size() const
{
    return vertices.size();
}

template <class T>
template <class S>
bool Polygon<T>::intersects(const S& shape)
{
    return Intersections::intersection(*this, shape);
}
