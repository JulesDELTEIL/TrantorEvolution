project(zappy_server)

########## SETUP ##########
set(SERV_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(SERV_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## BINARY ##########
add_executable( ${PROJECT_NAME}
    ${SERV_SRC_DIR}main.c
)

########## LINKAGE ##########
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        ${HDR_DIR}
        ${SERV_HDR_DIR}
)
