project(zappy_gui)
cmake_policy(SET CMP0072 NEW)

########## SETUP ##########
set(GUI_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(GUI_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## PACKAGES ##########
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${GUI_SRC_DIR}main.cpp
    ${GUI_SRC_DIR}core/Core.cpp
    ${GUI_SRC_DIR}core/Engine.cpp
    ${GUI_SRC_DIR}visual/AScene.cpp
    ${GUI_SRC_DIR}visual/ALayer.cpp
    ${GUI_SRC_DIR}visual/ADrawable.cpp
)

########## LINKAGE ##########
target_link_libraries( ${PROJECT_NAME}
    sfml-graphics
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${GUI_HDR_DIR}
)
