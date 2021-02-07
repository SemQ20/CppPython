cmake_minimum_required(VERSION 3.8)

project(test LANGUAGES C CXX)

set(TARGET test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Python COMPONENTS Interpreter Development)

add_executable(${TARGET} test.cpp)

target_link_libraries(${TARGET} Boost::unit_test_framework)
target_link_libraries(${TARGET} ${Python_LIBRARIES})
