#ifndef UTIL_H
#define UTIL_H


class Util
{
public:
    template <class T>
    static inline int fastFloor(const T& value)
    {
        int i = (int)value; /* truncate */
        return i - ( i > value ); /* convert trunc to floor */
    }
    template <class T>
    static inline int mod(const T& value, const T& div)
    {
        int r = value%div;
        if(r<0) r+=div;
        return r;
    }
protected:
private:
    Util(){}
    virtual ~Util(){}

};

#endif // UTIL_H
