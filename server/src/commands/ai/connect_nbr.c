/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

// ACTION
int action_connect_nbr(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_connect_nbr(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};

    if (strlen(data) != 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d", client->player->team->space_left);
    set_message(client, answer, NULL, sdata->debug);
    return EXIT_SUCCESS;
}
