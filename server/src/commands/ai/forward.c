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

// ACTION
int action_forward(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (move_player(client->player) == EXIT_FAILURE) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    keep_player_in(client->player, sdata->args->width, sdata->args->height);
    send_data(client, "ok", NULL, sdata->debug);
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_forward(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[FORWARD].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    set_action_end(client, sdata->args->freq, ACTIONS_ARR[FORWARD].delay);
    return EXIT_SUCCESS;
}
