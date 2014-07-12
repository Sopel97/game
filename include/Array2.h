#ifndef ARRAY2_H
#define ARRAY2_H

#include <vector>
#include <utility>
using std::size_t;

template <class T>
class Array2
{
public:
    class Stripe
    {
    public:
        Stripe() :
            m_dataStripe(nullptr),
            m_size(0)
        {

        }
        Stripe(T* dataStripe, size_t size) :
            m_dataStripe(dataStripe),
            m_size(size)
        {

        }
        Stripe(Stripe& stripe) :
            m_dataStripe(stripe.m_dataStripe),
            m_size(stripe.m_size)
        {

        }
        Stripe(Stripe&& stripe) :
            m_dataStripe(stripe.m_dataStripe),
            m_size(stripe.m_size)
        {

        }
        ~Stripe()
        {

        }
        T& operator[] (size_t y)
        {
            return *(m_dataStripe + y);
        }
        Stripe& operator= (Stripe && stripe)
        {
            m_dataStripe = stripe.m_dataStripe;
            m_size = stripe.m_size;
            return *this;
        }
        Stripe& operator= (const Stripe& stripe)
        {
            return operator= (std::move(Stripe(stripe)));
        }
        T* data() const
        {
            return m_dataStripe;
        }
        void fill(T& value)
        {
            for(size_t i = 0; i < m_size; ++i) m_dataStripe[i] = value;
        }

        size_t size() const
        {
            return m_size;
        }

        bool empty() const
        {
            return m_dataStripe == nullptr;
        }

        T* begin()
        {
            return m_dataStripe;
        }
        const T* begin() const
        {
            return m_dataStripe;
        }
        const T* cbegin() const
        {
            return m_dataStripe;
        }

        T* end()
        {
            return m_dataStripe + m_size;
        }
        const T* end() const
        {
            return m_dataStripe + m_size;
        }
        const T* cend() const
        {
            return m_dataStripe + m_size;
        }
    private:
        T* m_dataStripe;
        size_t m_size;
    };
    Array2() :
        m_data(nullptr),
        m_sizeX(0),
        m_sizeY(0)
    {

    }
    Array2(size_t sizeX, size_t sizeY) :
        m_sizeX(sizeX),
        m_sizeY(sizeY)
    {
        m_data = new T[m_sizeX * m_sizeY];
    }
    Array2(size_t sizeX, size_t sizeY, T& initValue) :
        Array2(sizeX, sizeY)
    {
        size_t totalSize = m_sizeX * m_sizeY;
        m_data = new T[totalSize];
        for(size_t i = 0; i < totalSize; ++i)
        {
            m_data[i] = initValue;
        }
    }
    Array2(const Array2<T>& arrayCopy) :
        m_sizeX(arrayCopy.m_sizeX),
        m_sizeY(arrayCopy.m_sizeY)
    {
        size_t totalSize = m_sizeX * m_sizeY;
        m_data = new T[totalSize];
        for(size_t i; i < totalSize; ++i) m_data[i] = arrayCopy.m_data[i];
    }
    Array2(Array2<T>&& array) :
        m_data(std::move(array.m_data)),
        m_sizeX(array.m_sizeX),
        m_sizeY(array.m_sizeY)
    {

    }
    ~Array2()
    {
        delete m_data;
    }

    Stripe operator[] (size_t x)
    {
        return Stripe(m_data + x * m_sizeY, m_sizeY);
    }
    T& operator() (size_t x, size_t y)
    {
        return m_data[x * m_sizeY + y];
    }

    Array2& operator= (Array2<T> && array)
    {
        m_data = std::move(array.m_data);
        m_sizeX = array.m_sizeX;
        m_sizeY = array.m_sizeY;
        return *this;
    }
    Array2& operator= (const Array2<T>& arrayCopy)
    {
        return operator=(std::move(Array2(arrayCopy)));
    }
    void fill(T& value)
    {
        size_t totalSize = m_sizeX * m_sizeY;
        for(size_t i = 0; i < totalSize; ++i)
        {
            m_data[i] = value;
        }
    }

    T* data() const
    {
        return m_data;
    }

    size_t sizeX() const
    {
        return m_sizeX;
    }

    size_t sizeY() const
    {
        return m_sizeY;
    }

    std::pair<size_t, size_t> size() const
    {
        return std::pair<size_t, size_t>(m_sizeX, m_sizeY);
    }

    bool empty() const
    {
        return m_data == nullptr;
    }

    T* begin()
    {
        return m_data;
    }
    const T* begin() const
    {
        return m_data;
    }
    const T* cbegin() const
    {
        return m_data;
    }

    T* end()
    {
        size_t totalSize = m_sizeX * m_sizeY;
        return m_data + totalSize;
    }
    const T* end() const
    {
        size_t totalSize = m_sizeX * m_sizeY;
        return m_data + totalSize;
    }
    const T* cend() const
    {
        size_t totalSize = m_sizeX * m_sizeY;
        return m_data + totalSize;
    }



private:
    T* m_data;
    size_t m_sizeX;
    size_t m_sizeY;
};



#endif // ARRAY2_H
