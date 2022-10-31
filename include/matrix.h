#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <cmath>
#include <iostream>

#include "array.h"
#include "errors.h"

template <typename Type, size_t rows = 1, size_t cols = 1>
class Matrix {
public:
  Matrix() : m(rows), n(cols) {
    allocate();

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] = 0;
  }

  Matrix(size_t m, size_t n) : m(m), n(n) {
    allocate();

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] = 0;
  }

  Matrix(Type **array, size_t m, size_t n) : m(m), n(n) {
    allocate();

    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        arr[i][j] = array[i][j];
  }

  Matrix(std::initializer_list<std::initializer_list<Type>> list)
      : m(list.size()), n(list.begin()->size()) {
    allocate();

    int i = 0, j;
    for (auto &row : list) {
      j = 0;
      for (auto &value : row)
        arr[i][j++] = value;
      i++;
    }
  }

  Matrix(std::initializer_list<Array<Type>> list)
      : m(list.size()), n(list.begin()->size()) {
    allocate();

    size_t i = 0;
    for (const Array<Type> &array : list) {
      for (size_t j = 0; j < array.size(); j++)
        arr[i][j] = array[j];
      i++;
    }
  }

  Matrix(const Matrix<Type> &matrix) : m(matrix.m), n(matrix.n) {
    allocate();

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] = matrix.arr[i][j];
  }

  Matrix(Matrix<Type> &&matrix) : m(matrix.m), n(matrix.n) {
    arr = matrix.arr;
    matrix.arr = nullptr;
    matrix.m = 0;
    matrix.n = 0;
  }

  ~Matrix() {
    for (size_t i = 0; i < m; i++)
      delete[] arr[i];
    delete[] arr;
  }

  inline Type &operator()(const size_t i, const size_t j) const {
    return arr[i][j];
  }

  inline Type *operator[](const size_t i) const { return arr[i]; }

  Matrix<Type> &operator=(const Matrix<Type> &matrix) {
    if (this == &matrix)
      return *this;

    if (m != matrix.m || n != matrix.n) {
      for (size_t i = 0; i < m; i++)
        delete[] arr[i];
      delete[] arr;

      m = matrix.m;
      n = matrix.n;
      allocate();
    }

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] = matrix.arr[i][j];

    return *this;
  }

  Matrix<Type> &operator+=(const Type number) {
    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] += number;

    return *this;
  }

  Matrix<Type> &operator+=(const Matrix<Type> &matrix) {
    if (m != matrix.sizeM() || n != matrix.sizeN())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] += matrix.arr[i][j];

    return *this;
  }

  Matrix<Type> &addArray(const Array<Type> &array, bool by_column = false) {
    if (by_column && m != array.size())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));
    else if (!by_column && n != array.size())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));

    if (by_column)
      for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
          arr[i][j] += array[i];
    else
      for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
          arr[i][j] += array[j];

    return *this;
  }

  Matrix<Type> &operator-=(const Type number) {
    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] -= number;

    return *this;
  }

  Matrix<Type> &operator-=(const Matrix<Type> &matrix) {
    if (m != matrix.sizeM() || n != matrix.sizeN())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] -= matrix.arr[i][j];

    return *this;
  }

  Matrix<Type> &subArray(const Array<Type> &array, bool by_column = false) {
    if (by_column && m != array.size())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));
    else if (!by_column && n != array.size())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));

    if (by_column)
      for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
          arr[i][j] -= array[i];
    else
      for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
          arr[i][j] -= array[j];

    return *this;
  }

  Matrix<Type> &operator*=(const Type number) {
    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] *= number;

    return *this;
  }

  Matrix<Type> &operator*=(const Matrix<Type> &matrix) {
    if (n != matrix.sizeM())
      throw(SizeError("Invalid sizes", __FILE__, __func__, __LINE__));

    Matrix res(m, matrix.n);
    for (size_t i = 0; i < res.m; i++)
      for (size_t j = 0; j < res.n; j++)
        for (size_t k = 0; k < n; k++)
          res.arr[i][j] += (arr[i][k] * matrix.arr[k][j]);

    return (*this = res);
  }

  Array<Type> operator*(const Array<Type> &array) {
    if (n != array.size())
      throw(SizeError("Invalid sizes", __FILE__, __func__, __LINE__));

    Array<Type> res(m);
    Type tmp;

    for (size_t i = 0; i < m; i++) {
      tmp = 0;
      for (size_t j = 0; j < n; j++) {
        tmp += arr[i][j] * array[j];
      }
      res.add(tmp);
    }

    return res;
  }

  Matrix<Type> &operator/=(const Type number) {
    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        arr[i][j] /= number;

    return *this;
  }

  Array<Type> getDiagonal() {
    size_t min_dim = std::min(n, m);
    Array<Type> array(min_dim);
    for (size_t i = 0; i < min_dim; i++)
      array.add(arr[i][i]);

    return array;
  }

  Array<Type> getRow(size_t const index) {
    Array<Type> array(arr[index], n);

    return array;
  }

  Array<Type> getColumn(size_t const index) {
    Array<Type> array(m);
    for (int i = 0; i < m; i++)
      array.add(arr[i][index]);

    return array;
  }

  Matrix<Type> transpose() {
    Matrix res(n, m);
    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        res.arr[j][i] = arr[i][j];

    return res;
  }

  Matrix<Type> getCofactor() {
    if (sizeN() != sizeM())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));

    Matrix<Type> res(n, n);
    Matrix<Type> subMatrix(n - 1, n - 1);

    for (size_t i = 0; i < n; i++)
      for (size_t j = 0; j < n; j++) {
        int p = 0;
        for (size_t x = 0; x < n; x++) {
          if (x == i)
            continue;

          int q = 0;

          for (size_t y = 0; y < n; y++) {
            if (y == j)
              continue;

            subMatrix[p][q] = arr[x][y]; //получение новой матрицы без i-той
                                         //строки и j-го столбца
            q++;
          }
          p++;
        }
        res[i][j] = pow(-1, i + j) * subMatrix.getDeterminant();
      }

    return res;
  }

  Type getDeterminant() {
    if (sizeN() != sizeM())
      throw(SizeError("Different sizes", __FILE__, __func__, __LINE__));

    if (n == 0)
      return 1;

    if (n == 1)
      return arr[0][0];

    if (n == 2)
      return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];

    Type res = 0;
    int sign = 1, p;
    for (size_t i = 0; i < n; i++) {
      Matrix<Type> subMatrix(n - 1, n - 1);

      for (size_t j = 1; j < n; j++) {
        p = 0;

        for (size_t k = 0; k < n; k++)
          if (k != i) {
            subMatrix[j - 1][p] = arr[j][k]; //получение матрицы, которая не
                                             //находится в строке и столбце i
            p++;
          }
      }

      res = res + sign * arr[0][i] * subMatrix.getDeterminant();
      sign = -sign;
    }

    return res;
  }

  Matrix<double> inverse() {
    Matrix<double> res(m, n);
    Type D = getDeterminant();
    if (D == 0) {
      throw(DataError("Determinant = 0", __FILE__, __func__, __LINE__));
      return res;
    }

    double inverse_D = 1.0 / D;

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        res[i][j] = arr[i][j];

    res = res.getCofactor().transpose();

    for (size_t i = 0; i < m; i++)
      for (size_t j = 0; j < n; j++)
        res[i][j] *= inverse_D;

    return res;
  }

  size_t sizeM() const { return m; }

  size_t sizeN() const { return n; }

private:
  Type **arr;
  size_t m;
  size_t n;

  void allocate() {
    arr = new Type *[m];
    for (size_t i = 0; i < m; i++)
      arr[i] = new Type[n];
  }
};

template <typename Type, size_t rows = 0, size_t cols = 0>
std::ostream &operator<<(std::ostream &os,
                         const Matrix<Type, rows, cols> &matrix) {
  for (size_t i = 0; i < matrix.sizeM(); i++) {
    for (size_t j = 0; j < matrix.sizeN(); j++)
      os << matrix[i][j] << " ";
    os << std::endl;
  }

  return os;
}

#endif // MATRIX_H
