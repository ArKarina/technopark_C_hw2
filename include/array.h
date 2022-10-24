#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename Type, size_t arr_n = 1> class Array {
public:
  Array() : n(arr_n), realSize(0) {
    arr = new Type[n];

    for (size_t i = 0; i < n; i++)
      arr[i] = 0;
  }
  Array(size_t _n) : n(_n), realSize(0) {
    arr = new Type[n];

    for (size_t i = 0; i < n; i++)
      arr[i] = 0;
  }

  Array(Type *array, size_t n) : n(n), realSize(n) {
    arr = new Type[n];

    for (size_t i = 0; i < n; i++)
      arr[i] = array[i];
  }

  Array(std::initializer_list<Type> list) : n(list.size()), realSize(0) {
    arr = new Type[n];

    for (auto &value : list)
      arr[realSize++] = value;
  }

  Array(const Array<Type> &array) : n(array.n), realSize(array.realSize) {
    arr = new Type[n];

    for (size_t i = 0; i < n; i++)
      arr[i] = array.arr[i];
  }

  Array(Array<Type> &&array) : n(array.n), realSize(array.realSize) {
    arr = array.arr;
    array.arr = nullptr;
    array.n = 0;
    array.realSize = 0;
  }

  ~Array() { delete[] arr; }

  inline Type &operator()(const size_t i) const { return arr[i]; }
  inline Type &operator[](const size_t i) const { return arr[i]; }

  Array<Type> &operator=(const Array<Type> &array) {
    if (this == &array)
      return *this;

    if (n != array.n) {
      delete[] arr;

      n = array.n;
      realSize = 0;
      arr = new Type[n];
    }
    realSize = 0;

    for (size_t i = 0; i < array.realSize; i++)
      arr[realSize++] = array.arr[i];

    return *this;
  }

  Array<Type> &operator+=(const Type number) {
    for (size_t i = 0; i < n; i++)
      arr[i] += number;

    return *this;
  }

  Array<Type> &operator+=(const Array<Type> &array) {
    for (size_t i = 0; i < n; i++)
      arr[i] += array.arr[i];

    return *this;
  }

  Array<Type> &operator-=(const Type number) {
    for (size_t i = 0; i < n; i++)
      arr[i] -= number;

    return *this;
  }

  Array<Type> &operator-=(const Array<Type> &array) {
    for (size_t i = 0; i < n; i++)
      arr[i] -= array.arr[i];

    return *this;
  }

  Array<Type> &operator*=(const Type number) {
    for (size_t i = 0; i < n; i++)
      arr[i] *= number;

    return *this;
  }

  Array<Type> &operator*=(const Array<Type> &array) {
    for (size_t i = 0; i < n; i++)
      arr[i] *= array.arr[i];

    return *this;
  }

  void add(Type elem) { arr[realSize++] = elem; }

  size_t size() const { return realSize; }

  Array<Type> slice(int start = 0, int stop = 0, int step = 1) {
    if (start < 0)
      start += realSize;

    if (start > realSize - 1) {
      std::cout << "Invalid start value" << std::endl;
      return *this;
    }

    if (stop < 0)
      stop += realSize;
    else if (stop == 0)
      stop = realSize;

    if (stop > realSize) {
      std::cout << "Invalid stop value" << std::endl;
      return *this;
    }

    if (stop < start) {
      if (step > 0)
        std::cout << "Invalid slice values" << std::endl;

      std::swap(start, stop);
      step *= -1;
    }

    Array<Type> res(n);
    if (step >= 0)
      for (size_t i = start; i < stop; i += step)
        res.add(arr[i]);
    else
      for (int i = stop - 1; i >= start; i += step)
        res.add(arr[i]);

    return res;
  }

private:
  Type *arr;
  size_t realSize;
  size_t n;
};

template <typename Type, size_t arr_n = 1>
std::ostream &operator<<(std::ostream &os, const Array<Type> &array) {
  if (array.size() == 0) {
    os << "Array is empty.";
    return os;
  }

  for (size_t i = 0; i < array.size(); i++)
    os << array[i] << " ";
  os << std::endl;

  return os;
}

#endif // ARRAY_H