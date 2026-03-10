cmake_minimum_required(VERSION 3.25)

project(cpu_observer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)



