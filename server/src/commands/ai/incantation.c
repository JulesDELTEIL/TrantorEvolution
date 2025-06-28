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

static const bool level_up_ok(serverdata_t *sdata, player_t *player)
{
    int nb_players = 6;
    tile_t tile;

    printf("%d\n", nb_players);
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

static void set_player_incantation_end(player_t *player, size_t timer_end)
{
    player->action.cmd = strdup(ACTIONS_ARR[INCANTATION].name);
    player->action.data = strdup("");
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
            printf("\033[34mThe incantation from client %d (player %d, level %d) triggered incantation of client %d (player %d, level %d)\033[0m\n", client->fd, client->player->id,client->player->level, fdarray->clients[k].fd, fdarray->clients[k].player->id, fdarray->clients[k].player->level); // COMMENT TO REMEMBER TO REMOVE
            set_player_incantation_end(fdarray->clients[k].player, timer_end);
            set_message(&(fdarray->clients[k]), "Elevation underway", NULL);
        }
    }
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

    if (level_up_ok(sdata, client->player))
        client->player->level += 1;
    if (client->player->level >= 8)
        client->player->team->level_max += 1;
    sprintf(answer, "Current level: %d", client->player->level);
    set_message(client, answer, NULL);
    send_gui_p_end_inc(sdata, fdarray, client);
    check_game_end(sdata, fdarray, client);
    printf("\033[34mClient %d (player %d) incantation done, actual level %d\033[0m\n", client->fd, client->player->id, client->player->level); // COMMENT TO REMEMBER TO REMOVE
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
        printf("\033[34mIncantation command from client %d (player %d, level %d) accepted\033[0m\n", client->fd, client->player->id, client->player->level); // COMMENT TO REMEMBER TO REMOVE
        set_player_incantation_end(client->player,
            set_timer_end(sdata->args->freq, ACTIONS_ARR[INCANTATION].delay));
        set_message(client, "Elevation underway", NULL);
        send_gui_p_start_inc(sdata, fdarray, client);
    } else {
        set_message(client, "ko", NULL);
    }
    return EXIT_SUCCESS;
}
