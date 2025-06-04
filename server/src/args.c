/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** checkargs.c
*/

#include <dirent.h>
#include <stdlib.h>

#include "app.h"
#include "functions.h"

static void get_port(char *arg, arguments_t *args)
{
    if (arg == NULL)
        return;
    args->port = atoi(arg);
}

void get_args(int ad, char *av[], arguments_t *args)
{
    size_t flw = 1;

    args->debug = false;
    for (; flw < ad; flw++) {
        if (strcmp(av[flw], ARG_DEBUG) == 0)
            args->debug = true;
        if (strcmp(av[flw], ARG_PORT) == 0)
            get_port(av[flw + 1], args);
    }
}

int check_args(arguments_t *args)
{
    if (args->port < MIN_PORT || args->port > MAX_PORT) {
        display_usage();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
