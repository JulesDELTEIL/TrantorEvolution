/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** functions.h
*/

#ifndef APP_H_
    #define APP_H_

    #include <stdbool.h>
    #include "structs.h"

    #define PROCESS_FAILURE 84
    #define PROCESS_SUCCESS 0

    #define MIN_PORT 1025
    #define MAX_PORT 65535

    #define ARG_PORT "-p"
    #define ARG_MAP "-m"
    #define ARG_DEBUG "-d"

static const char *USAGE_MSG[] = {
    "./zappy_server -p <port> [-d]\n"
};

int display_usage(void);

void get_args(int ad, char *av[], arguments_t *args);

int check_args(arguments_t *args);

#endif
