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

static void rotate_player(player_t *player)
{
    int res = player->orientation + 1;

    if (res > W)
        res = N;
    player->orientation = res;
}

static void send_gui_p_moved(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %d %d %d",
        client->player->id,
        client->player->pos.x,
        client->player->pos.y,
        client->player->orientation
    );
    send_guis(sdata, fdarray, M_PPO, data);
}

// ACTION
int action_right(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    rotate_player(client->player);
    set_message(client, M_OK, NULL);
    send_gui_p_moved(sdata, fdarray, client);
}

// COMMAND
int cmd_right(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[RIGHT].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[RIGHT].delay);
    return EXIT_SUCCESS;
}
