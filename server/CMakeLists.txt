project(zappy_server)

########## SETUP ##########
set(SERVER_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(SERVER_CMD_DIR "${PROJECT_SOURCE_DIR}/src/commands/")
set(SERVER_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")
set(SERVER_THR_DIR "${PROJECT_SOURCE_DIR}/src/map_thread/") 

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${SERVER_SRC_DIR}main.c
    ${SERVER_SRC_DIR}args.c
    ${SERVER_SRC_DIR}usage.c
    ${SERVER_SRC_DIR}setup.c
    ${SERVER_SRC_DIR}loop.c
    ${SERVER_SRC_DIR}connection.c
    ${SERVER_SRC_DIR}transmission.c
    ${SERVER_SRC_DIR}commands.c
    ${SERVER_SRC_DIR}timer.c
    ${SERVER_SRC_DIR}debug.c
    ${SERVER_SRC_DIR}returnwitherror.c
    ${SERVER_SRC_DIR}end.c
    ${SERVER_SRC_DIR}init_game.c
    ${SERVER_CMD_DIR}tna.c
    ${SERVER_CMD_DIR}msz.c
    ${SERVER_CMD_DIR}bct.c
    ${SERVER_THR_DIR}init_map.c
    ${SERVER_THR_DIR}init_thread.c
)

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${SERVER_HDR_DIR}
)