/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** forward.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

static void rotate_player(player_t *player)
{
    int res = player->orientation - 1;

    if (res < N)
        res = W;
    player->orientation = res;
}

// ACTION
int action_left(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    rotate_player(client->player);
    send_data(client, "ok", NULL, sdata->debug);
}

// COMMAND
int cmd_left(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[LEFT].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[LEFT].delay);
    return EXIT_SUCCESS;
}
