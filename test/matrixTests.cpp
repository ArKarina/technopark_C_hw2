#include <iostream>

#include "matrix.h"
#include "gtest/gtest.h"

TEST(MatrixTest, ElemByIndex) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};

  ASSERT_EQ(m1[1][0], 6);
  ASSERT_EQ(m1(2, 1), 7);
}

TEST(MatrixTest, getRow) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};

  Array<int> a1 = {6, 3, 9};
  Array<int> a2 = m1.getRow(1);
  for (size_t i = 0; i < a1.size(); i++)
    ASSERT_EQ(a1[i], a2[i]);
}

TEST(MatrixTest, getColumn) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};

  Array<int> a1 = {1, 6, 2};
  Array<int> a2 = m1.getColumn(0);
  for (size_t i = 0; i < a1.size(); i++)
    ASSERT_EQ(a1[i], a2[i]);
}

TEST(MatrixTest, getDiagonal) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};

  Array<int> a1 = {1, 3, 3};
  Array<int> a2 = m1.getDiagonal();
  for (size_t i = 0; i < a1.size(); i++)
    ASSERT_EQ(a1[i], a2[i]);

  m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}, {1, 2, 3}};
  a2 = m1.getDiagonal();
  for (size_t i = 0; i < a1.size(); i++)
    ASSERT_EQ(a1[i], a2[i]);
}

TEST(MatrixTest, constructors) {
  ASSERT_NO_THROW(Matrix<double>(10, 20));
  ASSERT_NO_THROW(Matrix<double>());
  Matrix<int, 3, 4> m1;
  ASSERT_EQ(m1[1][1], 0);
  ASSERT_NO_THROW(Matrix<double>({{1, 5, 2}, {6, 3, 9}, {2, 7, 3}, {1, 2, 3}}));

  Array<int> a1 = {1, 3, 3, 5};
  Array<int> a2 = {1, 4, 3, 4};
  ASSERT_NO_THROW(Matrix<int>({a1, a2}));
}

TEST(MatrixTest, AddMatrices) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};
  Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix<int> res = {{2, 7, 5}, {10, 8, 15}, {9, 15, 12}};
  m1 += m2;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, AddArray) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}};
  Array<int> a1 = {1, 2, 3};
  Matrix<int> res = {{2, 7, 5}, {7, 5, 12}};
  m1.addArray(a1);

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);

  a1 = {2, 1};
  res = {{4, 9, 7}, {8, 6, 13}};
  m1.addArray(a1, true);

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, AddNumber) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};
  Matrix<int> res = {{2, 6, 3}, {7, 4, 10}, {3, 8, 4}};
  m1 += 1;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, SubMatrices) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};
  Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix<int> res = {{0, 3, -1}, {2, -2, 3}, {-5, -1, -6}};
  m1 -= m2;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, SubArray) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}};
  Array<int> a1 = {1, 2, 3};
  Matrix<int> res = {{0, 3, -1}, {5, 1, 6}};
  m1.subArray(a1);

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);

  a1 = {2, 1};
  res = {{-2, 1, -3}, {4, 0, 5}};
  m1.subArray(a1, true);

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, SubNumber) {
  Matrix<int> m1 = {{2, 6, 3}, {7, 4, 10}, {3, 8, 4}};
  Matrix<int> res = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};
  m1 -= 1;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, MultiplyMatrices) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};
  Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix<int> res = {{35, 43, 51}, {81, 99, 117}, {51, 63, 75}};
  m1 *= m2;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);

  m1 = {{2, 1}, {-3, 0}, {4, -1}};
  m2 = {{5, -1, 6}, {-3, 0, 7}};
  res = {{7, -2, 19}, {-15, 3, -18}, {23, -4, 17}};
  m1 *= m2;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, MultiplyArray) {
  Matrix<int> m1 = {{2, 4, 0}, {-2, 1, 3}, {-1, 0, 1}};
  Array<int> a1 = {1, 2, -1};
  Array<int> res1 = {10, -3, -2};
  Array<int> tmp = m1 * a1;

  for (size_t i = 0; i < res1.size(); i++)
    ASSERT_EQ(tmp[i], res1[i]);

  m1 = {{2, 4, 0}, {-2, 1, 3}, {-1, 0, 1}};
  Matrix<int> a2 = {{1}, {2}, {-1}};
  Matrix<int> res = {{10}, {-3}, {-2}};
  m1 *= a2;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, MultiplyNumber) {
  Matrix<int> m1 = {{1, 5, 2}, {6, 3, 9}, {2, 7, 3}};
  Matrix<int> res = {{2, 10, 4}, {12, 6, 18}, {4, 14, 6}};
  m1 *= 2;

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m1[i][j], res[i][j]);
}

TEST(MatrixTest, getTranspose) {
  Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix<int> m2 = m1.transpose();
  Matrix<int> res = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m2[i][j], res[i][j]);

  m1 = {{1, 2, 3}, {4, 5, 6}};
  m2 = m1.transpose();
  res = {{1, 4}, {2, 5}, {3, 6}};

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m2[i][j], res[i][j]);
}

TEST(MatrixTest, getInverse) {
  Matrix<int> m1 = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  Matrix<double> m2 = m1.inverse();
  Matrix<double> res = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m2[i][j], res[i][j]);

  m1 = {{1, 2}, {3, 4}};
  m2 = m1.inverse();
  res = {{-2, 1}, {1.5, -0.5}};

  for (size_t i = 0; i < res.sizeM(); i++)
    for (size_t j = 0; j < res.sizeN(); j++)
      ASSERT_EQ(m2[i][j], res[i][j]);
}

TEST(MatrixTest, getDeterminant) {
  Matrix<int> m1 = {{0, -1, 0}, {1, 3, -2}, {2, 5, -1}};
  ASSERT_EQ(m1.getDeterminant(), 3);

  m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  ASSERT_EQ(m1.getDeterminant(), 0);
}
