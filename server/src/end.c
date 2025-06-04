/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** end.c
*/

#include "functions.h"

int close_server(serverdata_t *sdata, fdarray_t *fdarray)
{
    close(sdata->sockfd);
    for (size_t k = 0; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].username != NULL)
            free(fdarray->clients[k].username);
    }
    return EXIT_SUCCESS;
}
