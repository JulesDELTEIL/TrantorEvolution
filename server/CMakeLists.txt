project(zappy_server)

########## SETUP ##########
set(SERVER_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(SERVER_AI_CMD_DIR "${PROJECT_SOURCE_DIR}/src/commands/ai/")
set(SERVER_GUI_CMD_DIR "${PROJECT_SOURCE_DIR}/src/commands/gui/")
set(SERVER_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")
set(SERVER_THR_DIR "${PROJECT_SOURCE_DIR}/src/game/map_thread/") 

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${SERVER_SRC_DIR}main.c
    ${SERVER_SRC_DIR}app/args.c
    ${SERVER_SRC_DIR}app/usage.c
    ${SERVER_SRC_DIR}network/setup.c
    ${SERVER_SRC_DIR}network/loop.c
    ${SERVER_SRC_DIR}network/connection.c
    ${SERVER_SRC_DIR}network/transmission.c
    ${SERVER_SRC_DIR}network/end.c
    ${SERVER_SRC_DIR}clients/commands.c
    ${SERVER_SRC_DIR}clients/actions.c
    ${SERVER_SRC_DIR}clients/set_team.c
    ${SERVER_SRC_DIR}clients/timer.c
    ${SERVER_SRC_DIR}utils/debug.c
    ${SERVER_SRC_DIR}utils/returnwitherror.c
    ${SERVER_SRC_DIR}game/player.c
    ${SERVER_SRC_DIR}game/init_game.c
    ${SERVER_AI_CMD_DIR}forward.c
    ${SERVER_AI_CMD_DIR}left.c
    ${SERVER_AI_CMD_DIR}right.c
    ${SERVER_AI_CMD_DIR}fork.c
    ${SERVER_AI_CMD_DIR}inventory.c
    ${SERVER_AI_CMD_DIR}connect_nbr.c
    ${SERVER_AI_CMD_DIR}set.c
    ${SERVER_AI_CMD_DIR}take.c
    ${SERVER_AI_CMD_DIR}broadcast.c
    ${SERVER_GUI_CMD_DIR}tna.c
    ${SERVER_GUI_CMD_DIR}msz.c
    ${SERVER_GUI_CMD_DIR}bct.c
    ${SERVER_GUI_CMD_DIR}mct.c
    ${SERVER_THR_DIR}init_map.c
    ${SERVER_THR_DIR}init_thread.c
)

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${SERVER_HDR_DIR}
)