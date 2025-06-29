/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** macros.h
*/

#ifndef SERVERMACROS_H_
    #define SERVERMACROS_H_

typedef unsigned int uint_t;

    #define DEFAULTRC -1
    #define NOFD -1

    #define TEMPBUFFSIZE 1024
    #define BUFFSIZE 1024
    #define POLLTIMEOUT 1 //milliseconds
    #define CLOSE_CONNECTION 12

    #define CLIENT_BUFFER_SIZE 1024

    #define CLOSE_PROCESS 12
    #define NBCLIENTS_MAX 200
    #define NBCLIENTS_QUEUE 100
    #define NB_SERVER_FD 2
    #define NBTOTAL_FD (NBCLIENTS_MAX + NB_SERVER_FD)

    #define SERVER_FD_INDEX 0
    #define SERVER_STDIN_INDEX 1

static const char ERROR_SETSOCKOPT[] = "ERROR: setsockopt() failed\n";
static const char ERROR_BIND[] = "ERROR: bind() failed\n";
static const char ERROR_POLL[] = "ERROR: poll() failed\n";
static const char ERROR_ACCEPT[] = "ERROR: accept() failed\n";
static const char CLIENTS_OVERFLOW_MSG[] =
"Maximum clients reached, try again later\n";

    #define CLIENTS_OVERFLOW_CODE 42

enum client_type_e {
    AI = 0,
    GUI = 1,
    UNSET = 2
};

static const char GRAPHIC_TEAM[] = "GRAPHIC";
static const char M_WELCOME[] = "WELCOME";

static const char PLAYER_STR_LEN = 6;

// fit with RESSOURCES_NAMES indexes
static const uint_t RESOURCES_STR_LEN[] = {
    4,
    8,
    9,
    5,
    8,
    6,
    8
};

    #define MAX_LEVEL 8
    #define NB_MAX_LVL_TO_WIN 6

#endif
