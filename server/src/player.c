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

static int del_player(game_t *game, int id)
{
    player_t *prev = NULL;

    while (game->players != NULL) {
        if (game->players->id == id) {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

static int add_player(game_t *game, client_t *client, char *team_name)
{
    player_t *new = malloc(sizeof(player_t));

    new->id = game->next;
    new->team = strdup(team_name);
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
        player->team
    );
    send_data(ui_client, "pnw", buff, sdata->debug);
    return EXIT_SUCCESS;
}

int new_player(serverdata_t *sdata, fdarray_t *fdarray, client_t *client,
    char *team_name)
{
    add_player(&(sdata->game_data), client, team_name);
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == GUI) {
            send_pnw(sdata, client->player, &(fdarray->clients[k]));
        }
    }
    return EXIT_SUCCESS;
}
