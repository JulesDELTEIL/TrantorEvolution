/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** check_gui.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    if (client == NULL || client->buffin == NULL)
        return EXIT_FAILURE;
    if (sdata->debug)
        debug_buffer(client);
    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < NB_COMMANDS[client->type]; k++)
        if (strcmp(cmd, COMMANDS[client->type][k].command) == 0)
            return COMMANDS[client->type][k].handler(sdata,
                fdarray, client, data);
    set_message(client, M_SUC, NULL);
    return EXIT_FAILURE;
}

int check_gui_client(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    return buffer_handler(sdata, fdarray, client);
}
