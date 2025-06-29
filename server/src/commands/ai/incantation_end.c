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

static bool is_in_incantation(int id, incantation_t incantation)
{
    for (uint_t k = 0; k < incantation.nb_players; k++)
        if (id == incantation.player_inc_ids[k])
            return true;
    return false;
}

static bool incantation_end_ok(serverdata_t *sdata, player_t *player)
{
    tile_t tile = sdata->game_data.map.tiles[player->pos.x][player->pos.y];
    int n = 0;
    player_t *head = sdata->game_data.players;

    while (head != NULL) {
        if (is_in_incantation(head->id, player->incantation))
            n++;
        head = head->next;
    }
    if (player->incantation.nb_players != n)
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
        if (sdata->game_data.teams[k].level_max >= NB_MAX_LVL_TO_WIN) {
            printf("\033[33mGAME END, Winner team : %s\033[0m\n",
                client->player->team->name);
            send_guis(sdata, fdarray, M_SEG, sdata->game_data.teams[k].name);
            sdata->is_running = false;
        }
    }
}

static int player_set_level(player_t *player, int level)
{
    player->level = level;
    if (player->level == MAX_LEVEL)
        player->team->level_max += 1;
}

static int affect_incantation_players(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    player_t *head = sdata->game_data.players;
    char answer[BUFFSIZE] = {0};

    sprintf(answer, "%d", client->player->level);
    for (uint_t k = NB_SERVER_FD; k < NBCLIENTS_MAX; k++) {
        if (fdarray->clients[k].type != AI)
            continue;
        if (is_in_incantation(fdarray->clients[k].player->id,
        client->player->incantation)) {
            player_set_level(fdarray->clients[k].player,
                client->player->incantation.level_after);
            set_message(&(fdarray->clients[k]), M_INC_END, answer);
        }
    }
}

// ACTION
int action_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char gui_msg[BUFFSIZE] = {0};

    if (client->player->incantation.starter == false)
        return EXIT_FAILURE;
    if (incantation_end_ok(sdata, client->player))
        affect_incantation_players(sdata, fdarray, client);
    client->player->incantation = (incantation_t){0};
    sprintf(gui_msg, "%d %d %d", client->player->pos.x,
        client->player->pos.y, client->player->level);
    send_guis(sdata, fdarray, M_PIE, gui_msg);
    check_game_end(sdata, fdarray, client);
}
