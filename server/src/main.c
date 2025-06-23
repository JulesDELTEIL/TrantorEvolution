/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** main.c
*/

#include <stdlib.h>

#include "app.h"

int main(int ac, char *av[])
{
    arguments_t args = {0};
    int rc = DEFAULTRC;

    if (ac < MIN_NB_ARGS) {
        display_usage();
        return 84;
    }
    get_args(ac, av, &args);
    if (check_args(&args) == EXIT_FAILURE) {
        display_usage();
        return PROCESS_FAILURE;
    }
    rc = server(&args);
    if (rc == EXIT_FAILURE)
        return PROCESS_FAILURE;
    return PROCESS_SUCCESS;
}
