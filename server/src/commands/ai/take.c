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

int cmd_take(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) == 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    rc = idt_resource(data);
    if (take_resource(sdata, client, rc) == EXIT_FAILURE)
        send_data(client, "ko", NULL, sdata->debug);
    else
        send_data(client, "ok", NULL, sdata->debug);
    set_action_end(client, sdata->args->freq, 7);
    return EXIT_SUCCESS;
}
