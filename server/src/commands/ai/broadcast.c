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

static int calculate_k(serverdata_t *sdata, client_t *sender, client_t *dest)
{
    return 0;
}

static int send_msg(serverdata_t *sdata, client_t *sender,
    client_t *dest, char *data)
{
    char answer[BUFSIZ] = {0};
    int k = calculate_k(sdata, sender, dest);

    sprintf(answer, "%d, %s", k, data);
    set_message(dest, "message", answer);
}

static int prepare_answer_message(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == AI &&
            (fdarray->clients[k].player->id != client->player->id))
            send_msg(sdata, client, &(fdarray->clients[k]), data);
    }
}

static void send_gui_p_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *msg)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %s",
        client->player->id,
        msg
    );
    send_guis(sdata, fdarray, "pbc", data);
}

int action_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    prepare_answer_message(sdata, fdarray, client, data);
    set_message(client, "ok", NULL);
    send_gui_p_broadcast(sdata, fdarray, client, data);
}

int cmd_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) == 0) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[BROADCAST].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[BROADCAST].delay);
    return EXIT_SUCCESS;
}
