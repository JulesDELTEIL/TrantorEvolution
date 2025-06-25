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
#include "commands.h"

static int del_egg(team_t *team, pos_t pos)
{
    egg_t *node = team->eggs->next;
    egg_t *prev = team->eggs;

    if (team->eggs->pos.x == pos.x && team->eggs->pos.y == pos.y) {
        team->eggs = prev->next;
        free(prev);
        return EXIT_SUCCESS;
    }
    while (node != NULL) {
        if (node->pos.x == pos.x && node->pos.y == pos.y) {
            prev->next = node->next;
            free(node);
            return EXIT_SUCCESS;
        }
        prev = node;
        node = node->next;
    }
    return EXIT_FAILURE;
}

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

static void drop_inventory(game_t *game, player_t *player)
{
    tile_t *tile = NULL;

    pthread_mutex_lock(&(game->map.mutex));
    tile = &(game->map.tiles[player->pos.x][player->pos.y]);
    for (uint_t k = 0; k < NB_RESOURCES; k++) {
        tile->resources[k] += player->inventory[k];
    }
    pthread_mutex_unlock(&(game->map.mutex));
}

int kill_player(serverdata_t *sdata, client_t *client)
{
    if (client->player == NULL)
        return EXIT_FAILURE;
    set_message(client, "dead", NULL, sdata->debug);
    drop_inventory(&(sdata->game_data), client->player);
    if (client->player->action.cmd != NULL)
        free(client->player->action.cmd);
    if (client->player->action.data != NULL)
        free(client->player->action.data);
    del_player(&(sdata->game_data), client->player->id);
    client->player = NULL;
    client->type = UNSET;
    return EXIT_SUCCESS;
}

static int set_action(player_t *player)
{
    player->action.status = NONE;
    player->action.end = 0;
    player->action.cmd = NULL;
    player->action.data = NULL;
}

static int add_player(game_t *game, client_t *client, team_t *team)
{
    player_t *new = malloc(sizeof(player_t));

    new->id = game->next;
    new->team = team;
    new->level = 1;
    if (team->eggs != NULL) {
        new->pos = team->eggs->pos;
        del_egg(team, new->pos);
    } else
        new->pos = game->spawn;
    new->orientation = N;
    set_action(new);
    for (uint_t k = 0; k < NB_DIFF_ITEMS; k++)
        new->inventory[k] = 0;
    new->inventory[FOOD] = NB_FOOD_BEGIN;
    new->next = game->players;
    game->players = new;
    client->player = new;
    game->next++;
}

int send_pnw(serverdata_t *sdata, player_t *player, client_t *ui_client)
{
    char buff[BUFFSIZE] = {0};

    sprintf(buff, "%d %d %d %d %d %s",
        player->id,
        player->pos.x,
        player->pos.y,
        player->orientation,
        player->level,
        player->team->name
    );
    set_message(ui_client, "pnw", buff, sdata->debug);
    return EXIT_SUCCESS;
}

static int find_team_idx(game_t *game, char *team_name)
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

    if (team_idx < 0 || sdata->game_data.teams[team_idx].space_left <= 0)
        return EXIT_FAILURE;
    add_player(&(sdata->game_data), client,
        &(sdata->game_data.teams[team_idx]));
    client->player->team->space_left -= 1;
    client->player->time_use_life = set_timer_end(sdata->args->freq,
        TICKS_FOOD_USE);
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == GUI) {
            send_pnw(sdata, client->player, &(fdarray->clients[k]));
        }
    }
    return EXIT_SUCCESS;
}
