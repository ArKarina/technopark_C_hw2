cmake_minimum_required(VERSION 3.16)
project(MatrixCalculator)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 11)
set(TEST_NAME ${PROJECT_NAME}_tests)
file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/*.cpp")
add_executable(${TEST_NAME} ${SRC})
target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
