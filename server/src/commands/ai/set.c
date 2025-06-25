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

static int set_resource(serverdata_t *sdata, client_t *client, int resource)
{
    int pl_x = client->player->pos.x;
    int pl_y = client->player->pos.y;

    if (resource < 0 || client->player->inventory[resource] == 0)
        return EXIT_FAILURE;
    client->player->inventory[resource] -= 1;
    pthread_mutex_lock(&(sdata->game_data.map.mutex));
    sdata->game_data.map.tiles[pl_x][pl_y].resources[resource] += 1;
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

static void send_gui_p_changed_inv(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %d %d %d %d %d %d %d %d %d",
        client->player->id,
        client->player->pos.x,
        client->player->pos.y,
        client->player->inventory[0],
        client->player->inventory[1],
        client->player->inventory[2],
        client->player->inventory[3],
        client->player->inventory[4],
        client->player->inventory[5],
        client->player->inventory[6]
    );
    send_guis(sdata, fdarray, "pin", data);
}

static void send_gui_p_set(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, int resource)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %d",
        client->player->id,
        resource
    );
    send_guis(sdata, fdarray, "pdr", data);
}

// ACTION
int action_set(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    int resource = idt_resource(data);

    if (set_resource(sdata, client, resource) == EXIT_FAILURE) {
        set_message(client, "ko", NULL, sdata->debug);
    } else {
        set_message(client, "ok", NULL, sdata->debug);
        send_gui_p_changed_inv(sdata, fdarray, client);
        send_gui_p_set(sdata, fdarray, client, resource);
    }
}

// COMMAND
int cmd_set(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) == 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[SET].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[SET].delay);
    return EXIT_SUCCESS;
}
