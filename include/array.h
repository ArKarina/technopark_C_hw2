#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <iostream>

#include "errors.h"

template <typename Type, size_t arr_n = 1>
class Array {
public:
  Array() : capacity(arr_n), real_size(0) {
    arr = new Type[capacity];

    for (size_t i = 0; i < capacity; i++)
      arr[i] = 0;
  }

  Array(size_t _capacity) : capacity(_capacity), real_size(0) {
    arr = new Type[capacity];

    for (size_t i = 0; i < capacity; i++)
      arr[i] = 0;
  }

  Array(Type *array, size_t capacity)
      : capacity(capacity), real_size(capacity) {
    arr = new Type[capacity];

    for (size_t i = 0; i < capacity; i++)
      arr[i] = array[i];
  }

  Array(std::initializer_list<Type> list)
      : capacity(list.size()), real_size(0) {
    arr = new Type[capacity];

    for (auto &value : list)
      arr[real_size++] = value;
  }

  Array(const Array<Type> &array)
      : capacity(array.capacity), real_size(array.real_size) {
    arr = new Type[capacity];

    for (size_t i = 0; i < capacity; i++)
      arr[i] = array.arr[i];
  }

  Array(Array<Type> &&array)
      : capacity(array.capacity), real_size(array.real_size) {
    arr = array.arr;
    array.arr = nullptr;
    array.capacity = 0;
    array.real_size = 0;
  }

  ~Array() { delete[] arr; }

  inline Type &operator()(const size_t i) const {
    if (i < 0 || i >= real_size || !arr)
      throw(IndexError("Invalid index", __FILE__, __func__, __LINE__));

    return arr[i];
  }

  inline Type &operator[](const size_t i) const {
    if (i < 0 || i >= real_size || !arr)
      throw(IndexError("Invalid index", __FILE__, __func__, __LINE__));

    return arr[i];
  }

  Array<Type> &operator=(const Array<Type> &array) {
    if (this == &array)
      return *this;

    if (capacity != array.capacity) {
      delete[] arr;

      capacity = array.capacity;
      arr = new Type[capacity];
    }
    real_size = 0;

    for (size_t i = 0; i < array.real_size; i++)
      arr[real_size++] = array.arr[i];

    return *this;
  }

  Array<Type> &operator+=(const Type number) {
    for (size_t i = 0; i < real_size; i++)
      arr[i] += number;

    return *this;
  }

  Array<Type> &operator+=(const Array<Type> &array) {
    if (array.size() != real_size)
      throw(SizeError("Invalid size", __FILE__, __func__, __LINE__));

    for (size_t i = 0; i < real_size; i++)
      arr[i] += array.arr[i];

    return *this;
  }

  Array<Type> &operator-=(const Type number) {
    for (size_t i = 0; i < real_size; i++)
      arr[i] -= number;

    return *this;
  }

  Array<Type> &operator-=(const Array<Type> &array) {
    if (array.size() != real_size)
      throw(SizeError("Invalid size", __FILE__, __func__, __LINE__));

    for (size_t i = 0; i < real_size; i++)
      arr[i] -= array.arr[i];

    return *this;
  }

  Array<Type> &operator*=(const Type number) {
    for (size_t i = 0; i < real_size; i++)
      arr[i] *= number;

    return *this;
  }

  Array<Type> &operator*=(const Array<Type> &array) {
    if (array.size() != real_size)
      throw(SizeError("Invalid size", __FILE__, __func__, __LINE__));

    for (size_t i = 0; i < real_size; i++)
      arr[i] *= array.arr[i];

    return *this;
  }

  void add(Type elem) {
    if (real_size >= capacity || !arr)
      throw(IndexError("Invalid index", __FILE__, __func__, __LINE__));

    arr[real_size++] = elem;
  }

  size_t size() const { return real_size; }

  Array<Type> slice(int start = 0, int stop = 0, int step = 1) {
    if (start < 0)
      start += real_size;

    if (start < 0 || start > real_size - 1) {
      throw(IndexError("Invalid start value", __FILE__, __func__, __LINE__));
      return *this;
    }

    if (stop < 0)
      stop += real_size;
    else if (stop == 0)
      stop = real_size;

    if (stop < 0 || stop > real_size) {
      throw(IndexError("Invalid stop value", __FILE__, __func__, __LINE__));
      return *this;
    }

    if (stop < start) {
      if (step > 0)
        throw(DataError("Invalid slice values", __FILE__, __func__, __LINE__));

      std::swap(start, stop);
      step *= -1;
    }

    Array<Type> res(capacity);
    if (step > 0)
      for (size_t i = start; i < stop; i += step)
        res.add(arr[i]);
    else
      for (int i = stop - 1; i >= start; i += step)
        res.add(arr[i]);

    return res;
  }

private:
  Type *arr;
  size_t real_size;
  size_t capacity;
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
