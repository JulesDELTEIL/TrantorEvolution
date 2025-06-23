/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** forward.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

static int send_message_to_all(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *msg)
{
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == AI &&
            (fdarray->clients[k].player->id != client->player->id))
            send_data(&(fdarray->clients[k]), "message", msg, sdata->debug);
    }
}

static int prepare_answer_message(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFSIZ] = {0};

    sprintf(answer, "%d, %s", 0, data);
    send_message_to_all(sdata, fdarray, client, answer);
}

int action_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    prepare_answer_message(sdata, fdarray, client, data);
    send_data(client, "ok", NULL, sdata->debug);
}

int cmd_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) == 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[BROADCAST].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    set_action_end(client, sdata->args->freq, ACTIONS_ARR[BROADCAST].delay);
    return EXIT_SUCCESS;
}
