/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** player.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serverdata.h"
#include "transmission.h"

int del_player(game_t *game, int id)
{
    player_t *node = game->players->next;
    player_t *prev = game->players;

    if (game->players->id == id) {
        game->players = prev->next;
        free(prev);
        return EXIT_SUCCESS;
    }
    while (node != NULL) {
        if (node->id == id) {
            prev->next = node->next;
            free(node);
            return EXIT_SUCCESS;
        }
        prev = node;
        node = node->next;
    }
    return EXIT_FAILURE;
}

static int add_player(game_t *game, client_t *client, team_t *team)
{
    player_t *new = malloc(sizeof(player_t));

    new->id = game->next;
    new->team = team;
    new->level = 0;
    new->x = 0;
    new->y = 0;
    new->orientation = N;
    for (uint_t k = 0; k < NB_DIFF_ITEMS; k++)
        new->inventory[k] = 0;
    new->next = game->players;
    game->players = new;
    client->player = new;
    game->next++;
}

static int send_pnw(serverdata_t *sdata, player_t *player, client_t *ui_client)
{
    char buff[BUFFSIZE] = {0};

    sprintf(buff, "%d %d %d %d %d %s",
        player->id,
        player->x,
        player->y,
        player->orientation,
        player->level,
        player->team->name
    );
    send_data(ui_client, "pnw", buff, sdata->debug);
    return EXIT_SUCCESS;
}

int find_team_idx(game_t *game, char *team_name)
{
    for (uint_t k = 0; k < game->nb_of_teams; k++)
        if (strcmp(game->teams[k].name, team_name) == 0)
            return k;
    return -1;
}

int new_player(serverdata_t *sdata, fdarray_t *fdarray, client_t *client,
    char *team_name)
{
    int team_idx = find_team_idx(&(sdata->game_data), team_name);

    if (team_idx < 0 || sdata->game_data.teams[team_idx].space_left <= 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    add_player(&(sdata->game_data), client,
        &(sdata->game_data.teams[team_idx]));
    sdata->game_data.teams[team_idx].space_left -= 1;
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == GUI) {
            send_pnw(sdata, client->player, &(fdarray->clients[k]));
        }
    }
    return EXIT_SUCCESS;
}
