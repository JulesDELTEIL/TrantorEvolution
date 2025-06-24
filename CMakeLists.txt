cmake_minimum_required(VERSION 3.10)
project(TrantorEvolution)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=gnu++20")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(HDR_DIR "${PROJECT_SOURCE_DIR}/include/")
set(PROJECT_OUT "${PROJECT_SOURCE_DIR}")

########## BINARYs ##########
add_subdirectory(server)
add_subdirectory(gui)
add_subdirectory(ia)
