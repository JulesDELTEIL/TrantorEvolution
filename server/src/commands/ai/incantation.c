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
#include "commands/incantation.h"

static int get_nb_tile_players(player_t *head, pos_t tilepos, int level)
{
    uint_t n = 0;

    while (head != NULL) {
        if (head->pos.x == tilepos.x &&
            head->pos.y == tilepos.y &&
            head->level == level) {
            n++;
        }
        head = head->next;
    }
    return n;
}

static const bool incantation_start_ok(serverdata_t *sdata, player_t *player)
{
    int nb_players = get_nb_tile_players(sdata->game_data.players,
        player->pos, player->level);
    tile_t tile;

    pthread_mutex_lock(&(sdata->game_data.map.mutex));
    tile = sdata->game_data.map.tiles[player->pos.x][player->pos.y];
    pthread_mutex_unlock(&(sdata->game_data.map.mutex));
    if (nb_players < ELEVATION_REQ[player->level].players)
        return false;
    for (uint_t k = 0; k < NB_RESOURCES; k++)
        if (tile.resources[k] < ELEVATION_REQ[player->level].resources[k])
            return false;
    return true;
}

static void set_player_incantation_end(player_t *player, size_t timer_end,
    incantation_t *incantation)
{
    player->action.cmd = strdup(ACTIONS_ARR[INCANTATION].name);
    player->action.data = strdup("");
    player->action.status = ONGOING;
    player->action.end = timer_end;
    player->incantation = incantation;
}

static int fill_players_ids(client_t *client, player_t *head, int *arr)
{
    int n = 0;

    while (head != NULL) {
        if (head->pos.x == client->player->pos.x &&
            head->pos.y == client->player->pos.y &&
            head->level == client->player->level) {
            arr[n] = head->id;
            n++;
        }
        head = head->next;
    }
    return n;
}

static incantation_t *set_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    incantation_t *incantation = malloc(sizeof(incantation_t));
    int nb_players = get_nb_tile_players(sdata->game_data.players,
        client->player->pos, client->player->level);
    int *id_arr = malloc(sizeof(int) * nb_players);
    player_t *head = sdata->game_data.players;
    int n = 0;

    if (!incantation || !id_arr)
        return NULL;
    n = fill_players_ids(client, sdata->game_data.players, id_arr);
    incantation->done = 0;
    incantation->nb_players = nb_players;
    incantation->player_inc_ids = id_arr;
    if (n != incantation->nb_players) {
        free(incantation->player_inc_ids);
        free(incantation);
        return NULL;
    }
    return incantation;
}

static void send_gui_p_start_inc(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, incantation_t *incantation)
{
    char data[BUFFSIZE] = {0};
    size_t timer_end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[INCANTATION].delay);

    sprintf(data, "%d %d %d %d", client->player->pos.x, client->player->pos.y,
        client->player->level, client->player->id);
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type != AI)
            continue;
        if (fdarray->clients[k].player->pos.x == client->player->pos.x &&
        fdarray->clients[k].player->pos.y == client->player->pos.y &&
        fdarray->clients[k].player->level == client->player->level &&
        fdarray->clients[k].player->id != client->player->id) {
            sprintf(data, "%s %d", data, fdarray->clients[k].player->id);
            set_player_incantation_end(fdarray->clients[k].player,
                timer_end, incantation);
            set_message(&(fdarray->clients[k]), "Elevation underway", NULL);
        }
    }
    send_guis(sdata, fdarray, "pic", data);
}

// COMMAND
int cmd_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    incantation_t *incantation = NULL;

    if (strlen(data) != 0) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    if (client->player->level < 8 && incantation_start_ok(sdata,
        client->player)) {
        incantation = set_incantation(sdata, fdarray, client);
        set_player_incantation_end(client->player,
            set_timer_end(sdata->args->freq, ACTIONS_ARR[INCANTATION].delay),
            incantation);
        set_message(client, "Elevation underway", NULL);
        send_gui_p_start_inc(sdata, fdarray, client, incantation);
    } else {
        set_message(client, "ko", NULL);
    }
    return EXIT_SUCCESS;
}
