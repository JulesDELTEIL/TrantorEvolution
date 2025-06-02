cmake_minimum_required(VERSION 3.10)
project(TrantorEvolution)

########## SETUP ##########
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## BINARYs ##########
add_subdirectory(server)
add_subdirectory(ui)
# add_subdirectory(ia)
