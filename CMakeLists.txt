cmake_minimum_required(VERSION 3.16)

project(CppPython LANGUAGES C CXX)
set(TARGET CppPython)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(${TARGET} main.cpp cpppython.cpp)


find_package(Python COMPONENTS Interpreter Development)
target_link_libraries(${TARGET} PRIVATE ${Python_LIBRARIES})
