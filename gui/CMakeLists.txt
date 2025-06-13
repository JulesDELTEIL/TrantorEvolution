project(zappy_gui)
########## SETUP ##########
set(GUI_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(GUI_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## PACKAGES ##########
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

########## PLUGINS ##########
add_subdirectory(plugins)

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${GUI_SRC_DIR}main.cpp
    ${GUI_SRC_DIR}core/Core.cpp
    ${GUI_SRC_DIR}core/Engine.cpp
    ${GUI_SRC_DIR}visual/AScene.cpp
    ${GUI_SRC_DIR}visual/scenes/DefaultScene.cpp
    ${GUI_SRC_DIR}visual/scenes/InGame.cpp
    ${GUI_SRC_DIR}visual/layers/DefaultLayer.cpp
    ${GUI_SRC_DIR}visual/layers/Land.cpp
)

########## LINKAGE ##########
target_link_libraries( ${PROJECT_NAME}
    sfml-graphics
    ECS::ECS
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${ECS_HDR_DIR}
        ${GUI_HDR_DIR}
)
