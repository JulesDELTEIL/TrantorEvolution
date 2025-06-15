/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** args.c
*/

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

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

static void get_team_name(size_t *flw, arguments_t *args, char *av[])
{
    int nb_of_teams = 0;

    *flw += NEXT_ARG;
    for (int tmp = *flw; av[tmp] != NULL && av[tmp][FIRST_CHAR] != '-'; tmp++)
        nb_of_teams++;
    args->team_name = malloc(sizeof(char *) * (nb_of_teams + 1));
    if (!args->team_name)
        return;
    for (int i = 0; i < nb_of_teams; i++) {
        args->team_name[i] = av[*flw];
        *flw += 1;
    }
    args->team_name[nb_of_teams] = NULL;
    *flw -= BACK_TO_FLAG;
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
        if (strcmp(av[flw], ARG_TNAME) == 0)
            get_team_name(&flw, args, av);
    }
}

int check_args(arguments_t *args)
{
    if (args->port < MIN_PORT || args->port > MAX_PORT)
        return EXIT_FAILURE;
    if (args->height < MIN_MAP_SIZE || args->height > MAX_MAP_SIZE)
        return EXIT_FAILURE;
    if (args->width < MIN_MAP_SIZE || args->width > MAX_MAP_SIZE)
        return EXIT_FAILURE;
    if (args->clientnb < MIN_CLIENTS || args->freq < MIN_FREQ)
        return EXIT_FAILURE;
    if (args->team_name[FIRST_TEAM_NAME] == NULL ||
        args->team_name[A_SECOND_TEAM] == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
