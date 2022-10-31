#include "array.h"
#include "matrix.h"

#include <iostream>
#include <vector>

int main(void) {
  Matrix<int> m1 = {{5, 2, 3}, {4, 7, 6}, {7, 8, 9}};

  std::cout << m1;

  Array<int> a1 = {1, 2, 3, 4, 5, 6, 7};
  Array<int> a2 = a1.slice(20, 4);
  std::cout << a2;


  return 0;
}