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

static int get_nb_tile_players(player_t *head, int *players_buff,
    pos_t tilepos, int level)
{
    uint_t flw = 0;

    while (head != NULL) {
        if (head->pos.x == tilepos.x && head->pos.y == tilepos.y
        && head->level == level) {
            players_buff[flw] = head->id;
            flw++;
        }
        head = head->next;
    }
    return flw;
}

static const bool level_up_ok(serverdata_t *sdata, player_t *player)
{
    int players_ids[NBCLIENTS_MAX] = {0};
    int nb_players = get_nb_tile_players(sdata->game_data.players,
        players_ids, player->pos, player->level);
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

static void send_gui_p_start_inc(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char data[BUFFSIZE] = {0};
    int players_ids[NBCLIENTS_MAX] = {0};
    int nbplayers = 0;

    sprintf(data, "%d %d %d %d",
        client->player->pos.x,
        client->player->pos.y,
        client->player->level,
        client->player->id
    );
    for (uint_t k = 0; k < nbplayers; k++)
        if (players_ids[k] != client->player->id)
            sprintf(data, "%s %d", data, players_ids[k]);
    send_guis(sdata, fdarray, "pic", data);
}

static void send_gui_p_end_inc(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %d %d",
        client->player->pos.x,
        client->player->pos.y,
        client->player->level
    );
    send_guis(sdata, fdarray, "pie", data);
}

// ACTION
int action_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};

    if (level_up_ok(sdata, client->player))
        client->player->level += 1;
    sprintf(answer, "Current level: %d", client->player->level);
    set_message(client, answer, NULL);
    send_gui_p_end_inc(sdata, fdarray, client);
}

// COMMAND
int cmd_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    if (client->player->level < 8 && level_up_ok(sdata, client->player)) {
        client->player->action.cmd = strdup(ACTIONS_ARR[INCANTATION].name);
        client->player->action.data = strdup(data);
        client->player->action.status = ONGOING;
        client->player->action.end = set_timer_end(sdata->args->freq,
            ACTIONS_ARR[INCANTATION].delay);
        set_message(client, "Elevation underway", NULL);
        send_gui_p_start_inc(sdata, fdarray, client);
    } else {
        set_message(client, "ko", NULL);
    }
    return EXIT_SUCCESS;
}
