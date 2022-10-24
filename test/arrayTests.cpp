#include <iostream>

#include "array.h"
#include "gtest/gtest.h"

TEST(ArrayTest, ElemByIndex) {
  Array<int> a1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  ASSERT_EQ(a1[6], 6);
  ASSERT_EQ(a1(7), 7);
}

TEST(ArrayTest, constructors) {
  ASSERT_NO_THROW(Array<int>(10));
  ASSERT_NO_THROW(Array<double>());
  ASSERT_NO_THROW(Array<double>({0, 1, 2, 3, 6, 7, 8, 9}));
}

TEST(ArrayTest, AddArrays) {
  Array<int> a1 = {1, 5, 2, 6, 3, 9, 2, 7, 3};
  Array<int> a2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Array<int> res = {2, 7, 5, 10, 8, 15, 9, 15, 12};
  a1 += a2;

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a1[i], res[i]);
}

TEST(ArrayTest, AddNumber) {
  Array<int> a1 = {1, 5, 2, 6, 3, 9, 2};
  Array<int> res = {2, 6, 3, 7, 4, 10, 3};
  a1 += 1;

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a1[i], res[i]);
}

TEST(ArrayTest, SubArrays) {
  Array<int> a1 = {1, 5, 2, 6, 3, 9, 2, 7, 3};
  Array<int> a2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Array<int> res = {0, 3, -1, 2, -2, 3, -5, -1, -6};
  a1 -= a2;

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a1[i], res[i]);
}

TEST(ArrayTest, SubNumber) {
  Array<int> a1 = {2, 6, 3, 7, 4, 10, 3};
  Array<int> res = {1, 5, 2, 6, 3, 9, 2};
  a1 -= 1;

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a1[i], res[i]);
}

TEST(ArrayTest, MultiplyArrays) {
  Array<int> a1 = {1, 5, 2, 6, 3, 9, 2};
  Array<int> a2 = {1, 2, 3, 4, 5, 6, 7};
  Array<int> res = {1, 10, 6, 24, 15, 54, 14};
  a1 *= a2;

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a1[i], res[i]);
}

TEST(ArrayTest, MultiplyNumber) {
  Array<int> a1 = {1, 5, 2, 6, 3, 9, 2};
  Array<int> res = {2, 10, 4, 12, 6, 18, 4};
  a1 *= 2;

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a1[i], res[i]);
}

TEST(ArrayTest, Slice) {
  Array<int> a1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Array<int> res = {3, 5, 7};
  Array<int> a2 = a1.slice(2, 8, 2);

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a2[i], res[i]);

  res = {7, 8, 9, 10};
  a2 = a1.slice(-4);

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a2[i], res[i]);

  res = {4, 5, 6, 7};
  a2 = a1.slice(3, -3);

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a2[i], res[i]);

  res = {1, 2, 3, 4};
  a2 = a1.slice(0, -6);

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a2[i], res[i]);

  res = {10, 8, 6, 4, 2};
  a2 = a1.slice(0, 0, -2);

  for (size_t i = 0; i < res.size(); i++)
    ASSERT_EQ(a2[i], res[i]);
}
