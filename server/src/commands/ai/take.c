/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** forward.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

static int take_resource(serverdata_t *sdata, client_t *client, int resource)
{
    int pl_x = client->player->pos.x;
    int pl_y = client->player->pos.y;

    if (resource < 0 ||
        sdata->game_data.map.tiles[pl_x][pl_y].resources[resource] == 0)
        return EXIT_FAILURE;
    client->player->inventory[resource] += 1;
    pthread_mutex_lock(&(sdata->game_data.map.mutex));
    sdata->game_data.map.tiles[pl_x][pl_y].resources[resource] -= 1;
    pthread_mutex_unlock(&(sdata->game_data.map.mutex));
    return EXIT_SUCCESS;
}

static int idt_resource(char *data)
{
    for (uint_t k = 0; k < NB_RESOURCES; k++)
        if (strcmp(RESOURCES_NAMES[k], data) == 0)
            return k;
    return -1;
}

// ACTION
int action_take(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (take_resource(sdata, client, idt_resource(data)) == EXIT_FAILURE)
        set_message(client, "ko", NULL, sdata->debug);
    else
        set_message(client, "ok", NULL, sdata->debug);
}

// COMMAND
int cmd_take(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) == 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[TAKE].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[TAKE].delay);
    return EXIT_SUCCESS;
}
