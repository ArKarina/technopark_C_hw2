cmake_minimum_required(VERSION 3.16)
project(run_tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include/)
file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/*.cpp")
#[[ file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp") ]]

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} MatrixCalculator)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})