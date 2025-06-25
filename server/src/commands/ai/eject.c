/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** eject.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

// ACTION
int action_eject(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFSIZ] = {0};

    set_message(client, "ok", NULL);
}

// COMMAND
int cmd_eject(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[EJECT].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[EJECT].delay);
    return EXIT_SUCCESS;
}
