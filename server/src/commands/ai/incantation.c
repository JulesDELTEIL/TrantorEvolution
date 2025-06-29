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

static void set_incantation(serverdata_t *sdata, client_t *client)
{
    incantation_t incantation = {0};
    player_t *head = sdata->game_data.players;

    incantation.nb_players = 0;
    while (head != NULL) {
        if (head->pos.x == client->player->pos.x &&
            head->pos.y == client->player->pos.y &&
            head->level == client->player->level) {
            incantation.player_inc_ids[incantation.nb_players] = head->id;
            incantation.nb_players++;
        }
        head = head->next;
    }
    incantation.starter = true;
    incantation.level_after = client->player->level + 1;
    client->player->incantation = incantation;
}

static const bool incantation_start_ok(serverdata_t *sdata, client_t *client)
{
    tile_t tile = sdata->game_data.map.tiles
        [client->player->pos.x][client->player->pos.y];

    set_incantation(sdata, client);
    if (client->player->incantation.nb_players <
    ELEVATION_REQ[client->player->level].players) {
        client->player->incantation = (incantation_t){0};
        return false;
    }
    for (uint_t k = 0; k < NB_RESOURCES; k++)
        if (tile.resources[k] <
        ELEVATION_REQ[client->player->level].resources[k]) {
            client->player->incantation = (incantation_t){0};
            return false;
        }
    return true;
}

static void set_player_incantation_end(player_t *player, size_t timer_end)
{
    player->action.cmd = strdup(ACTIONS_ARR[INCANTATION].name);
    player->action.data = NULL;
    player->action.status = ONGOING;
    player->action.end = timer_end;
}

static void send_gui_p_start_inc(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
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
            set_player_incantation_end(fdarray->clients[k].player, timer_end);
            fdarray->clients[k].player->incantation.starter = false;
            set_message(&(fdarray->clients[k]), M_INC_START, NULL);
        }
    }
    send_guis(sdata, fdarray, M_PIC, data);
}

// COMMAND
int cmd_incantation(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, M_KO, NULL);
        return EXIT_FAILURE;
    }
    if (client->player->level < MAX_LEVEL &&
        incantation_start_ok(sdata, client)) {
        set_player_incantation_end(client->player,
            set_timer_end(sdata->args->freq, ACTIONS_ARR[INCANTATION].delay));
        set_message(client, M_INC_START, NULL);
        send_gui_p_start_inc(sdata, fdarray, client);
    } else {
        set_message(client, M_KO, NULL);
    }
    return EXIT_SUCCESS;
}
