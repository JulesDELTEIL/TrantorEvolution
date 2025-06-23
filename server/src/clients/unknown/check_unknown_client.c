/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** check_unknown.c
*/

#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "actions.h"
#include "debug.h"
#include "functions.h"
#include "transmission.h"

static int buffer_handler(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    if (client == NULL || client->buffer == NULL)
        return EXIT_FAILURE;
    if (sdata->debug)
        debug_buffer(client);
    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return set_team(sdata, fdarray, client, cmd);
}

int check_unknown_client(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    return buffer_handler(sdata, fdarray, client);
}
