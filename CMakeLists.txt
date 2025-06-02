cmake_minimum_required(VERSION 3.10)
project(default_project_name)

########## SETUP ##########
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${SRC_DIR}main.cpp
)

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
)
