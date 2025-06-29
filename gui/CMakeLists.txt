project(zappy_gui)

########## SETUP ##########
set(GUI_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(GUI_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## PACKAGES ##########
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${GUI_SRC_DIR}main.cpp
    ${GUI_SRC_DIR}maths/hitbox.cpp
    ${GUI_SRC_DIR}core/Core.cpp
    ${GUI_SRC_DIR}core/Engine.cpp
    ${GUI_SRC_DIR}core/Parser.cpp
    ${GUI_SRC_DIR}visual/AScene.cpp
    ${GUI_SRC_DIR}visual/Drawable.cpp
    ${GUI_SRC_DIR}visual/Animation.cpp
    ${GUI_SRC_DIR}visual/Movement.cpp
    ${GUI_SRC_DIR}visual/Text.cpp

    # NETWORK
    ${GUI_SRC_DIR}network/Client.cpp
    ${GUI_SRC_DIR}network/Socket.cpp
    ${GUI_SRC_DIR}network/events.cpp

    # ENTITIES
    ${GUI_SRC_DIR}visual/entities/Tile.cpp
    ${GUI_SRC_DIR}visual/entities/Trantorian.cpp
    ${GUI_SRC_DIR}visual/entities/ResourceNode.cpp
    ${GUI_SRC_DIR}visual/entities/Hud.cpp
    ${GUI_SRC_DIR}visual/entities/IncantationObject.cpp
    ${GUI_SRC_DIR}visual/entities/Background.cpp
    ${GUI_SRC_DIR}visual/entities/Egg.cpp
    ${GUI_SRC_DIR}visual/entities/LoadingScreen.cpp

    # SCENES
    ${GUI_SRC_DIR}visual/scenes/Land.cpp

    # AUDIO 
    ${GUI_SRC_DIR}audio/SoundManage.cpp
)

########## LINKAGE ##########
target_link_libraries( ${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${GUI_HDR_DIR}
)
