project(zappy_gui)

########## SETUP ##########
set(GUI_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(GUI_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${GUI_SRC_DIR}main.cpp
)

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${GUI_HDR_DIR}
)