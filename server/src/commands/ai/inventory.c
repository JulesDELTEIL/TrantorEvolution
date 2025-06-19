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

int cmd_inventory(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    send_inventory(sdata, client);
    set_action_end(client, sdata->args->freq, 1);
    return EXIT_SUCCESS;
}
