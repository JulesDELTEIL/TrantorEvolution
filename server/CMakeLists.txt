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
    ${SERVER_CMD_DIR}tna.c
<<<<<<< HEAD
    ${SERVER_THR_DIR}init_map.c
=======
    ${SERVER_CMD_DIR}idn.c
    ${SERVER_CMD_DIR}msz.c
>>>>>>> c8e73faa43e510c8b5c40440eec8fca4e75ef4fd
)

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${SERVER_HDR_DIR}
)