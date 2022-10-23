cmake_minimum_required(VERSION 3.16)
project(MatrixCalculator)

#[[ include_directories(${PROJECT_SOURCE_DIR}/src) ]]
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})

add_executable(app ${SRC})

add_subdirectory(test)







#[[

set(src src/*.cpp)

include_directories(include)

add_executable(app ${SRC_FILES})





cmake_minimum_required(VERSION 3.14)

project (matrices)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(main ${SRC_FILES})

add_subdirectory(tests)














cmake_minimum_required(VERSION 3.10)

project("NumbersCounterLib")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

message("SOURCES = ${SOURCES}")
message("HEADERS = ${HEADERS}")

set(LIB_NAME numbers_counter)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(NumbersCounterLib_LIB ${LIB_NAME})
set(NumbersCounterLib_LIB ${NumbersCounterLib_LIB} PARENT_SCOPE)
set(NumbersCounterLib_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(NumbersCounterLib_INCLUDE_DIRS ${NumbersCounterLib_INCLUDE_DIRS} PARENT_SCOPE)

message("NumbersCounterLib_LIB = ${NumbersCounterLib_LIB}")
message("NumbersCounterLib_INCLUDE_DIRS = ${NumbersCounterLib_INCLUDE_DIRS}")

enable_testing()
add_subdirectory(tests) ]]