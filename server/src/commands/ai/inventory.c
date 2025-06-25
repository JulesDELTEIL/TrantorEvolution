/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

static int send_inventory(serverdata_t *sdata, client_t *client)
{
    char answer[BUFFSIZE] = {0};

    sprintf(answer,
    "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]",
    RESOURCES_NAMES[FOOD], client->player->inventory[FOOD],
    RESOURCES_NAMES[WOOD], client->player->inventory[WOOD],
    RESOURCES_NAMES[ROCK], client->player->inventory[ROCK],
    RESOURCES_NAMES[CLAY], client->player->inventory[CLAY],
    RESOURCES_NAMES[METAL], client->player->inventory[METAL],
    RESOURCES_NAMES[OIL], client->player->inventory[OIL],
    RESOURCES_NAMES[ANTIMATTER], client->player->inventory[ANTIMATTER]
    );
    set_message(client, answer, NULL, sdata->debug);
}

// ACTION
int action_inventory(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    send_inventory(sdata, client);
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_inventory(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[INVENTORY].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[INVENTORY].delay);
    return EXIT_SUCCESS;
}
