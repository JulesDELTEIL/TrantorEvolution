/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** main.c
*/

#include <stdlib.h>

#include "app.h"
#include "functions.h"

int main(int ac, char *av[])
{
    arguments_t args = {0};
    int rc = DEFAULTRC;

    if (ac < 3 || ac > 4) {
        display_usage();
        return 84;
    }
    get_args(ac, av, &args);
    if (check_args(&args) == EXIT_FAILURE)
        return PROCESS_FAILURE;
    rc = server_loop(&args);
    if (rc == EXIT_FAILURE)
        return PROCESS_FAILURE;
    return PROCESS_SUCCESS;
}
