#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

template <class T>
class Shape
{
public:
    Shape();

    virtual ~Shape();
};

typedef Shape<double> ShapeD;
typedef Shape<float> ShapeF;
typedef Shape<int> ShapeI;

#endif // SHAPE_H_INCLUDED
