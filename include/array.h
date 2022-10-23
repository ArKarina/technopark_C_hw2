#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename Type, size_t arr_n = 1>
class Array
{
public:
    Array() : n(arr_n), realSize(0)
    {
        arr = new Type[n];

        for (size_t i = 0; i < n; i++)
            arr[i] = 0;
    }
    Array(size_t _n) : n(_n), realSize(0)
    {
        arr = new Type[n];

        for (size_t i = 0; i < n; i++)
            arr[i] = 0;
    }

    Array(Type* array, size_t n) : n(n), realSize(n)
    {
        arr = new Type[n];

        for (size_t i = 0; i < n; i++)
            arr[i] = array[i];
    }

    Array(std::initializer_list<Type> list) : n(list.size()), realSize(0)
    {
        arr = new Type[n];

        for (auto &value : list)
            arr[realSize++] = value;
    }

    Array(const Array<Type>& array) : n(array.n), realSize(array.realSize)
    {
        arr = new Type[n];

        for (size_t i = 0; i < n; i++)
            arr[i] = array.arr[i];
    }

    Array(Array<Type>&& array) : n(array.n), realSize(array.realSize)
    {
        arr = array.arr;
        array.arr = nullptr;
        array.n = 0;
        array.realSize = 0;
    }

    ~Array()
    {
        delete[] arr;
    }

    inline Type& operator()(const size_t i) const
    {
        return arr[i];
    }
    inline Type& operator[](const size_t i) const
    {
        return arr[i];
    }

    Array<Type>& operator=(const Array<Type>& array)
    {
        if (this == &array)
            return *this;

        if (n != array.n)
        {
            delete[] arr;

            n = array.n;
            realSize = 0;
            arr = new Type[n];
        }

        for (size_t i = 0; i < n; i++)
            arr[realSize++] = array.arr[i];

        return *this;
    }

    Array<Type>& operator+=(const Type number)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] += number;

        return *this;
    }

    Array<Type>& operator+=(const Array<Type>& array)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] += array.arr[i];

        return *this;
    }

    Array<Type>& operator-=(const Type number)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] -= number;

        return *this;
    }

    Array<Type>& operator-=(const Array<Type>& array)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] -= array.arr[i];

        return *this;
    }

    Array<Type>& operator*=(const Type number)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] *= number;

        return *this;
    }

    Array<Type>& operator*=(const Array<Type>& array)
    {
        for (size_t i = 0; i < n; i++)
            arr[i] *= array.arr[i];

        return *this;
    }

    void add(Type elem)
    {
        arr[realSize++] = elem;
    }

    size_t size() const
    {
        return realSize;
    }

private:
    Type* arr;
    size_t realSize;
    size_t n;
};

template <typename Type, size_t arr_n = 1>
std::ostream& operator<<(std::ostream& os, const Array<Type>& array)
{
    if (array.size() == 0)
    {
        os << "Array is empty.";
        return os;
    }

    for (size_t i = 0; i < array.size(); i++)
        os << array[i] << " ";
    os << std::endl;

    return os;

}

#endif // ARRAY_H