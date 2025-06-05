project(zappy_gui)
cmake_policy(SET CMP0072 NEW)

########## SETUP ##########
set(GUI_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(GUI_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${GUI_SRC_DIR}main.cpp
)

########## PACKAGES ##########
find_package(OpenGL REQUIRED)
find_package(SFML 2.5.1 COMPONENTS window audio REQUIRED)

########## LINKAGE ##########
target_link_libraries( ${PROJECT_NAME}
    OpenGL::GL
    sfml-audio
    sfml-window
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${GUI_HDR_DIR}
)
