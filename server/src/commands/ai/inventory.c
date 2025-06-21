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
    "[food %d, wood %d, rock %d, clay %d, metal %d, petrol %d, antimatter %d]",
    client->player->inventory[FOOD],
    client->player->inventory[WOOD],
    client->player->inventory[ROCK],
    client->player->inventory[CLAY],
    client->player->inventory[METAL],
    client->player->inventory[PETROL],
    client->player->inventory[ANTIMATTER]
    );
    send_data(client, answer, NULL, sdata->debug);
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
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[INVENTORY].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    set_action_end(client, sdata->args->freq, 1);
    return EXIT_SUCCESS;
}
