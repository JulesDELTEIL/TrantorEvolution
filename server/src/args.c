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

static void get_height(char *arg, arguments_t *args)
{
    if (arg == NULL)
        return;
    args->height = atoi(arg);
}

static void get_width(char *arg, arguments_t *args)
{
    if (arg == NULL)
        return;
    args->width = atoi(arg);
}

static void get_port(char *arg, arguments_t *args)
{
    if (arg == NULL)
        return;
    args->port = atoi(arg);
}

static void get_clientnb(char *arg, arguments_t *args)
{
    if (arg == NULL)
        return;
    args->clientnb = atoi(arg);
}

static void get_freq(char *arg, arguments_t *args)
{
    if (arg == NULL)
        return;
    args->freq = atoi(arg);
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
        if (strcmp(av[flw], ARG_WIDTH) == 0)
            get_width(av[flw + 1], args);
        if (strcmp(av[flw], ARG_HEIGHT) == 0)
            get_height(av[flw + 1], args);
        if (strcmp(av[flw], ARG_CLIENTS) == 0)
            get_clientnb(av[flw + 1], args);
        if (strcmp(av[flw], ARG_FREQ) == 0)
            get_freq(av[flw + 1], args);
    }
}

int check_args(arguments_t *args)
{
    if (args->port < MIN_PORT || args->port > MAX_PORT) {
        display_usage();
        return EXIT_FAILURE;
    }
    if (args->height < MIN_MAP_SIZE || args->height > MAX_MAP_SIZE) {
        display_usage();
        return EXIT_FAILURE;
    }
    if (args->width < MIN_MAP_SIZE || args->width > MAX_MAP_SIZE) {
        display_usage();
        return EXIT_FAILURE;
    }
    if (args->clientnb < MIN_CLIENTS) {
        display_usage();
        return EXIT_FAILURE;
    }
    if (args->freq < MIN_FREQ) {
        display_usage();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
