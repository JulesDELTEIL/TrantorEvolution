cmake_minimum_required(VERSION 3.15)
project(ZappyAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
message(STATUS "Using Python3 include: ${Python3_INCLUDE_DIRS}")
message(STATUS "Using Python3 lib:     ${Python3_LIBRARIES}")

add_executable(zappy_ai main.cpp)

target_link_libraries(zappy_ai PRIVATE Python3::Python)