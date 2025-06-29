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
#include "commands/look.h"

static uint_t calc_tileinfo_size(uint_t nb_players, tile_t tile)
{
    uint_t size = nb_players * (PLAYER_STR_LEN + 1);

    for (uint_t i = 0; i < NB_DIFF_ITEMS; i++)
        size += tile.resources[i] * (RESOURCES_STR_LEN[i] + 1);
    return size;
}

static uint_t calc_answer_size(serverdata_t *sdata, client_t *client)
{
    uint_t nb_tile = NB_TILES_LOOK[client->player->level];
    uint_t total_len = 1;
    pos_t vect = {0};
    pos_t tilepos = {0};
    uint_t nb_player = 0;
    tile_t tile;

    for (uint_t i = 0; i < nb_tile; i++) {
        vect = LOOK_TILES[client->player->orientation][i];
        tilepos = get_map_coor(sdata, client->player->pos, vect);
        nb_player = get_nb_tile_players(sdata, tilepos);
        if (tilepos.x == 0 && tilepos.y == 0)
            nb_player--;
        pthread_mutex_lock(&sdata->game_data.map.mutex);
        tile = sdata->game_data.map.tiles[tilepos.x][tilepos.y];
        pthread_mutex_unlock(&sdata->game_data.map.mutex);
        total_len += calc_tileinfo_size(nb_player, tile) + 1;
    }
    return total_len + 1;
}

static int my_snprintf(uint_t *offset, uint_t *remaining, char *tileinfo,
    const char *str)
{
    int written;

    written = snprintf((tileinfo) + (*offset), (*remaining), "%s ", str);
    if (written < 0 || (uint_t)written >= (*remaining)) {
        return EXIT_FAILURE;
    }
    (*offset) += written;
    (*remaining) -= written;
    return EXIT_SUCCESS;
}

static int fill_ressources(uint_t **follows, char *tileinfo, tile_t tile,
    uint_t k)
{
    for (uint_t i = 0; i < tile.resources[k]; i++)
        if (my_snprintf(follows[0], follows[1], tileinfo, RESOURCES_NAMES[k])
            == EXIT_FAILURE)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static char *fill_tile_data(serverdata_t *sdata, uint_t nb_players,
    tile_t tile)
{
    uint_t remaining = calc_tileinfo_size(nb_players, tile) + 1;
    uint_t offset = 0;
    char *tileinfo = calloc(remaining, sizeof(char));
    uint_t *follows[2];

    if (!tileinfo)
        return NULL;
    for (uint_t k = 0; k < nb_players; k++)
        if (my_snprintf(&offset, &remaining, tileinfo, "player")
            == EXIT_FAILURE)
            return NULL;
    follows[0] = &offset;
    follows[1] = &remaining;
    for (uint_t k = 0; k < NB_DIFF_ITEMS; k++)
        if (fill_ressources(follows, tileinfo, tile, k) == EXIT_FAILURE)
            return NULL;
    if (*follows[0] > 0 && tileinfo[*follows[0] - 1] == ' ')
        tileinfo[*follows[0] - 1] = '\0';
    return tileinfo;
}

static char *get_tile_data(serverdata_t *sdata, client_t *client, pos_t vect)
{
    pos_t tilepos = get_map_coor(sdata, client->player->pos, vect);
    tile_t tile;
    uint_t nb_players = get_nb_tile_players(sdata, tilepos);

    if (tilepos.x == 0 && tilepos.y == 0)
        nb_players -= 1;
    pthread_mutex_lock(&(sdata->game_data.map.mutex));
    tile = sdata->game_data.map.tiles[tilepos.x][tilepos.y];
    pthread_mutex_unlock(&(sdata->game_data.map.mutex));
    return fill_tile_data(sdata, nb_players, tile);
}

static int fill_tiles(serverdata_t *sdata, client_t *client, char *answer,
    uint_t **follows)
{
    pos_t vect;
    char *tileinfo = NULL;
    uint_t nbtiles = NB_TILES_LOOK[client->player->level];
    int written;

    for (uint_t k = 0; k < nbtiles; k++) {
        vect = LOOK_TILES[client->player->orientation][k];
        tileinfo = get_tile_data(sdata, client, vect);
        if (!tileinfo)
            return EXIT_FAILURE;
        written = snprintf(answer + *follows[0], *follows[1],
            (k < nbtiles - 1) ? "%s," : "%s", tileinfo);
        free(tileinfo);
        if (written < 0 || (uint_t)written >= *follows[1])
            return EXIT_FAILURE;
        *follows[0] += written;
        *follows[1] -= written;
    }
    return EXIT_SUCCESS;
}

static int fill_answer(serverdata_t *sdata, client_t *client, char *answer,
    uint_t answer_size)
{
    uint_t remaining = answer_size;
    int written;
    uint_t offset = 0;
    uint_t nbtiles = NB_TILES_LOOK[client->player->level];
    uint_t *follows[2];

    written = snprintf(answer + offset, remaining, "[");
    if (written < 0 || (uint8_t)written >= remaining)
        return EXIT_FAILURE;
    offset += written;
    remaining -= written;
    follows[0] = &offset;
    follows[1] = &remaining;
    if (fill_tiles(sdata, client, answer, follows) == EXIT_FAILURE)
        return EXIT_FAILURE;
    written = snprintf(answer + *follows[0], *follows[1], "]");
    if (written < 0 || (uint_t)written >= *follows[1])
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

// ACTION
int action_look(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    uint_t answer_size = calc_answer_size(sdata, client) + 1;
    char *answer = calloc(answer_size, sizeof(char));

    if (!answer)
        return EXIT_FAILURE;
    if (client->player->level >= MAX_LEVEL) {
        set_message(client, M_KO, NULL);
        free(answer);
        return EXIT_FAILURE;
    } else {
        if (fill_answer(sdata, client, answer, answer_size) == EXIT_FAILURE) {
            set_message(client, M_KO, NULL);
            free(answer);
            return EXIT_FAILURE;
        } else {
            set_message(client, answer, NULL);
        }
    }
    free(answer);
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_look(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, M_KO, NULL);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[LOOK].name);
    client->player->action.data = NULL;
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[LOOK].delay);
    return EXIT_SUCCESS;
}
