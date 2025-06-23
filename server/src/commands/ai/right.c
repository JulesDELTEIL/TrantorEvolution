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
    player->orientation -= 1;
    if (player->orientation < N)
        player->orientation = W;
}

// ACTION
int action_right(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    rotate_player(client->player);
    send_data(client, "ok", NULL, sdata->debug);
}

// COMMAND
int cmd_right(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[RIGHT].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    set_action_end(client, sdata->args->freq, ACTIONS_ARR[RIGHT].delay);
    return EXIT_SUCCESS;
}
