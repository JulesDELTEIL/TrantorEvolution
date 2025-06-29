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

static int del_egg(team_t *team, size_t id)
{
    egg_t *node = team->eggs->next;
    egg_t *prev = team->eggs;

    if (team->eggs->id == id) {
        team->eggs = prev->next;
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

int kill_player(serverdata_t *sdata, fdarray_t *fdarray, client_t *client)
{
    char answer[BUFFSIZE] = {0};

    if (client->player == NULL)
        return EXIT_FAILURE;
    set_message(client, "dead", NULL);
    sprintf(answer, "%d", client->player->id);
    send_guis(sdata, fdarray, "pdi", answer);
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

static pos_t generate_player_spawn(serverdata_t *sdata)
{
    pos_t try = (pos_t){0, 0};
    try.x = rand() % (sdata->args->width - 1);
    try.y = rand() % (sdata->args->height - 1);
    while (sdata->game_data.map.tiles[try.x][try.y].biome == SEA) {
        try.x = rand() % sdata->args->width;
        try.y = rand() % sdata->args->height;
    }
    return try;
}

static pos_t set_player_spawn(serverdata_t *sdata, fdarray_t *fdarray,
    team_t *team)
{
    char gui_data[BUFFSIZE] = {0};
    egg_t *head = team->eggs;
    pos_t found;

    while (head != NULL) {
        if (head->next == NULL) {
            found = head->pos;
            sprintf(gui_data, "%d", (int)head->id);
            send_guis(sdata, fdarray, "ebo", gui_data);
            del_egg(team, head->id);
            return found;
        }
        head = head->next;
    }
    return generate_player_spawn(sdata);
}

static int add_player(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, team_t *team)
{
    player_t *new = malloc(sizeof(player_t));

    if (!new)
        return EXIT_FAILURE;
    new->id = sdata->game_data.next_player;
    new->team = team;
    new->level = 1;
    new->pos = set_player_spawn(sdata, fdarray, team);
    new->orientation = (rand() % 4) + 1;
    new->incantation = (incantation_t){0};
    set_action(new);
    for (uint_t k = 0; k < NB_DIFF_ITEMS; k++)
        new->inventory[k] = 0;
    new->inventory[FOOD] = NB_FOOD_BEGIN;
    new->next = sdata->game_data.players;
    sdata->game_data.players = new;
    client->player = new;
    sdata->game_data.next_player++;
    return EXIT_SUCCESS;
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
    set_message(ui_client, "pnw", buff);
    return EXIT_SUCCESS;
}

int new_player(serverdata_t *sdata, fdarray_t *fdarray, client_t *client,
    char *team_name)
{
    int teamidx = -1;

    for (uint_t k = 0; k < sdata->game_data.nb_of_teams; k++)
        if (strcmp(sdata->game_data.teams[k].name, team_name) == 0)
            teamidx = k;
    if (teamidx < 0 || sdata->game_data.teams[teamidx].space_left <= 0)
        return EXIT_FAILURE;
    if (add_player(sdata, fdarray, client,
        &(sdata->game_data.teams[teamidx])) == EXIT_FAILURE)
            return EXIT_FAILURE;
    client->player->team->space_left -= 1;
    client->player->time_use_life = set_timer_end(sdata->args->freq,
        TICKS_FOOD_USE);
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        if (fdarray->clients[k].type == GUI)
            send_pnw(sdata, client->player, &(fdarray->clients[k]));
    return EXIT_SUCCESS;
}
