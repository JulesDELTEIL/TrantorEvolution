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

static void keep_player_in(player_t *player, int width, int height)
{
    if (player->pos.x < 0)
        player->pos.x = width - 1;
    if (player->pos.x > width - 1)
        player->pos.x = 0;
    if (player->pos.y < 0)
        player->pos.y = height - 1;
    if (player->pos.y > height - 1)
        player->pos.y = 0;
}

static int move_player(player_t *player)
{
    if (player->orientation == N) {
        player->pos.y -= 1;
        return EXIT_SUCCESS;
    }
    if (player->orientation == S) {
        player->pos.y += 1;
        return EXIT_SUCCESS;
    }
    if (player->orientation == E) {
        player->pos.x += 1;
        return EXIT_SUCCESS;
    }
    if (player->orientation == W) {
        player->pos.x -= 1;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
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
    send_guis(sdata, fdarray, "ppo", data);
}

// ACTION
int action_forward(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (move_player(client->player) == EXIT_FAILURE) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    keep_player_in(client->player, sdata->args->width, sdata->args->height);
    set_message(client, "ok", NULL);
    send_gui_p_moved(sdata, fdarray, client);
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_forward(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[FORWARD].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[FORWARD].delay);
    return EXIT_SUCCESS;
}
