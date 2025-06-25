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
#include "look.h"

static int keep_on_map(int max_val, int val)
{
    if (val < 0)
        val = (val + max_val);
    if (val >= max_val)
        val = (val - max_val);
    return val;
}

static pos_t get_map_coor(serverdata_t *sdata, pos_t player_pos, pos_t vect)
{
    pos_t res;

    res.x = player_pos.x + vect.x;
    res.y = player_pos.y + vect.y;
    res.x = keep_on_map(sdata->args->width, res.x);
    res.y = keep_on_map(sdata->args->height, res.y);
    return res;
}

static int get_nb_tile_players(serverdata_t *sdata, pos_t tilepos)
{
    player_t *head = sdata->game_data.players;
    int res = 0;

    while (head != NULL) {
        if (head->pos.x == tilepos.x && head->pos.y == tilepos.y)
            res++;
        head = head->next;
    }
    return res;
}

static char *get_tile_data(serverdata_t *sdata, client_t *client,
    char *tileinfo, pos_t vect)
{
    pos_t tilepos = get_map_coor(sdata, client->player->pos, vect);
    tile_t tile;
    uint_t nb_players = get_nb_tile_players(sdata, tilepos);
    uint_t size = 0;

    if (tilepos.x == 0 && tilepos.y == 0)
        nb_players -= 1;
    pthread_mutex_lock(&(sdata->game_data.map.mutex));
    tile = sdata->game_data.map.tiles[tilepos.x][tilepos.y];
    pthread_mutex_unlock(&(sdata->game_data.map.mutex));
    for (uint_t k = 0; k < nb_players; k++)
        sprintf(tileinfo, "%s%s ", tileinfo, "player");
    for (uint_t k = 0; k < NB_DIFF_ITEMS; k++) {
        for (uint_t i = 0; i < tile.resources[k]; i++) {
            sprintf(tileinfo, "%s%s ", tileinfo, RESOURCES_NAMES[k]);
        }
    }
    size = strlen(tileinfo);
    if (tileinfo[size - 1] == ' ')
        tileinfo[size - 1] = 0;
}

static int fill_answer(serverdata_t *sdata, client_t *client, char *answer)
{
    pos_t vect;
    char tileinfo[BUFFSIZE];
    uint_t nbtiles = NB_TILES_LOOK[client->player->level];

    sprintf(answer, "[");
    for (uint_t k = 0; k < nbtiles - 1; k++) {
        for (uint_t i = 0; i < BUFFSIZE; i++)
            tileinfo[i] = 0;
        vect = LOOK_TILES[client->player->orientation][k];
        get_tile_data(sdata, client, tileinfo, vect);
        sprintf(answer, "%s%s,", answer, tileinfo);
    }
    for (uint_t i = 0; i < BUFFSIZE; i++)
        tileinfo[i] = 0;
    vect = LOOK_TILES[client->player->orientation][nbtiles - 1];
    get_tile_data(sdata, client, tileinfo, vect);
    sprintf(answer, "%s%s]", answer, tileinfo);
}

// ACTION
int action_look(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFSIZ] = {0};

    fill_answer(sdata, client, answer);
    set_message(client, answer, NULL, sdata->debug);
}

// COMMAND
int cmd_look(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[LOOK].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[LOOK].delay);
    return EXIT_SUCCESS;
}
