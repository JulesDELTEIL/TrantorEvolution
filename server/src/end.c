/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** end.c
*/

#include <stdlib.h>
#include <unistd.h>

#include "serverdata.h"
#include "fdarray.h"

int destroy_client(client_t *client)
{
    if (client == NULL)
        return EXIT_FAILURE;
    if (client->buffer != NULL)
        free(client->buffer);
    if (client->team != NULL)
        free(client->team);
    return EXIT_SUCCESS;
}

void destroy_args(arguments_t *args)
{
    for (int i = 0; args->team_name[i] != NULL; i++)
        free(args->team_name[i]);
    free(args->team_name);
}

int close_server(serverdata_t *sdata, fdarray_t *fdarray)
{
    close(sdata->sockfd);
    for (size_t k = 0; k < NBTOTAL_FD; k++) {
        destroy_client(&(fdarray->clients[k]));
    }
    destroy_args(sdata->args);
    return EXIT_SUCCESS;
}
