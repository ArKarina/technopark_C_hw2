cmake_minimum_required(VERSION 3.16)
project(MatrixCalculator)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

add_executable(app ${SRC})

add_subdirectory(test)
