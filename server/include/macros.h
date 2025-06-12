/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** macros.h
*/

#ifndef SERVERMACROS_H_
    #define SERVERMACROS_H_

    #define DEFAULTRC -1
    #define NOFD -1

    #define TEMPBUFFSIZE 1024
    #define BUFFSIZE 1024
    #define POLLTIMEOUT 1 //milliseconds
    #define CRLF_LEN 2

    #define CLOSE_PROCESS 12

    #define NBCLIENTS_MAX 500
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

#endif
