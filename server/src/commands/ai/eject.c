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
#include "eject.h"

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

static int eject_players(serverdata_t *sdata, client_t *client)
{
    pos_t pos = client->player->pos;
    player_t *head = sdata->game_data.players;
    bool ejected = false;

    while (head != NULL) {
        if (head->id != client->player->id &&
            head->pos.x == pos.x && head->pos.y == pos.y) {
            head->pos.x += EJECT_DIR[client->player->orientation].x;
            head->pos.y += EJECT_DIR[client->player->orientation].y;
            keep_player_in(head, sdata->args->width, sdata->args->height);
            ejected = true;
        }
        head = head->next;
    }
    return ejected;
}

// ACTION
int action_eject(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (eject_players(sdata, client))
        set_message(client, "ok", NULL);
    else
        set_message(client, "ko", NULL);
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
