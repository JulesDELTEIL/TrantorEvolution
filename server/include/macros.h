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

    #define CLIENT_BUFFER_SIZE 1024

    #define CLOSE_PROCESS 12
    #define NBCLIENTS_MAX 100
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
    UNSET = -1,
    AI = 0,
    GUI = 1,
};

#endif
