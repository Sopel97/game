template <class T>
Shape2<T>::Shape2()
{

}

template <class T>
Mesh<LineSegment<T>> Shape2<T>::outline() const
{
    return Mesh<LineSegment<T>>();
}

template <class T>
Shape2<T>::~Shape2()
{

}
