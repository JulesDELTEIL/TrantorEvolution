project(ECS)

########## PACKAGES ##########
find_package(SFML 2.5.1 COMPONENTS graphics system REQUIRED)

########## SETUP ##########
set(ECS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(ECS_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

########## LIBRARY ##########
add_library(${PROJECT_NAME}
    STATIC
        ${ECS_SRC_DIR}AEntity.cpp
        ${ECS_SRC_DIR}ADrawable.cpp
        ${ECS_SRC_DIR}AObject.cpp
        ${ECS_SRC_DIR}AAnimated.cpp
)

add_library(ECS::ECS ALIAS ${PROJECT_NAME})

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ${ECS_HDR_DIR}
)