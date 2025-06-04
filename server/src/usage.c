/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** usage.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "app.h"

int display_usage(void)
{
    int nb_lines = sizeof(USAGE_MSG) / sizeof(USAGE_MSG[0]);

    for (size_t k = 0; k < nb_lines; k++)
        write(1, USAGE_MSG[k], strlen(USAGE_MSG[k]));
    return PROCESS_FAILURE;
}
