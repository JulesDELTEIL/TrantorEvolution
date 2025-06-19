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
    printf("#%s#\n", answer);
    send_message_to_all(sdata, fdarray, client, answer);
}

int cmd_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) == 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    prepare_answer_message(sdata, fdarray, client, data);
    send_data(client, "ok", NULL, sdata->debug);
    set_action_end(client, sdata->args->freq, 7);
    return EXIT_SUCCESS;
}
