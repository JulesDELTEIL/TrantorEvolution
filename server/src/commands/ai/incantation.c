/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** incantation.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"
#include "incantation.h"

static int get_nb_tile_players(player_t *head, pos_t tilepos)
{
    int res = 0;

    while (head != NULL) {
        if (head->pos.x == tilepos.x && head->pos.y == tilepos.y)
            res++;
        head = head->next;
    }
    return res;
}

static const bool level_up_ok(serverdata_t *sdata, player_t *player)
{
    int nb_players = get_nb_tile_players(sdata->game_data.players,
        player->pos);
    tile_t tile = sdata->game_data.map.tiles[player->pos.x][player->pos.y];

    if (nb_players < ELEVATION_REQ[player->level].players)
        return false;
    for (uint_t k = 0; k < NB_RESOURCES; k++)
        if (tile.resources[k] < ELEVATION_REQ[player->level].resources[k])
            return false;
    return true;
}

// ACTION
int action_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};

    if (level_up_ok(sdata, client->player))
        client->player->level += 1;
    sprintf(answer, "Current level: %d", client->player->level);
    send_data(client, answer, NULL, sdata->debug);
}

// COMMAND
int cmd_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    if (level_up_ok(sdata, client->player)) {
        client->player->action.cmd = strdup(ACTIONS_ARR[INCANTATION].name);
        client->player->action.data = strdup(data);
        client->player->action.status = ONGOING;
        client->player->action.end = set_timer_end(sdata->args->freq,
            ACTIONS_ARR[INCANTATION].delay);
        send_data(client, "Elevation underway", NULL, sdata->debug);
    } else {
        send_data(client, "ko", NULL, sdata->debug);
    }
    return EXIT_SUCCESS;
}
