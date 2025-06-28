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

static void check_destroy_incantation(serverdata_t *sdata, player_t *player,
    int n_pl)
{
    player->incantation->done += 1;
    if (player->incantation->done >= player->incantation->nb_players) {
        free(player->incantation->player_inc_ids);
        free(player->incantation);
        player->incantation = NULL;
        return;
    }
    if (player->incantation->done >= n_pl) {
        free(player->incantation->player_inc_ids);
        free(player->incantation);
        player->incantation = NULL;
        return;
    }
}

static bool incantation_end_ok(serverdata_t *sdata, player_t *player)
{
    tile_t tile = sdata->game_data.map.tiles[player->pos.x][player->pos.y];
    int nbplayers = player->incantation->nb_players;
    int n = 0;
    player_t *mt = NULL;

    for (uint_t k = 0; k < player->incantation->nb_players; k++) {
        mt = get_player_pos(sdata, player->incantation->player_inc_ids[k]);
        if (mt && mt->pos.x == player->pos.x && mt->pos.y == player->pos.y)
            n++;
    }
    check_destroy_incantation(sdata, player, n);
    if (n < nbplayers)
        return false;
    for (uint_t k = 0; k < NB_RESOURCES; k++)
        if (tile.resources[k] < ELEVATION_REQ[player->level].resources[k])
            return false;
    return true;
}

static int check_game_end(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    for (uint_t k = 0; k < sdata->game_data.nb_of_teams; k++) {
        if (sdata->game_data.teams[k].level_max >= 6) {
            printf("\033[33mGAME END, Winner team : %s\033[0m\n",
                client->player->team->name);
            send_guis(sdata, fdarray, "seg", sdata->game_data.teams[k].name);
            sdata->is_running = false;
        }
    }
}

// ACTION
int action_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};

    if (incantation_end_ok(sdata, client->player))
        client->player->level += 1;
    if (client->player->level >= 8)
        client->player->team->level_max += 1;
    sprintf(answer, "Current level: %d", client->player->level);
    set_message(client, answer, NULL);
    for (uint_t k = 0; k < BUFFSIZE; k++)
        answer[k] = 0;
    sprintf(answer, "%d %d %d", client->player->pos.x,
        client->player->pos.y, client->player->level);
    send_guis(sdata, fdarray, "pie", answer);
    check_game_end(sdata, fdarray, client);
}
