/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** idn.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"

int cmd_pin(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;
    player_t *player = NULL;

    if (strlen(data) == 0) {
        send_data(client, "sbp", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    player = get_player_pos(sdata, atoi(data));
    if (player == NULL) {
        send_data(client, "sbp", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d %d %d %d %d %d %d %d %d",
    player->pos.x, player->pos.y,
    player->inventory[FOOD], player->inventory[WOOD], player->inventory[ROCK],
    player->inventory[CLAY], player->inventory[METAL], player->inventory[OIL],
    player->inventory[ANTIMATTER]);
    send_data(client, "pin", answer, sdata->debug);
    return EXIT_SUCCESS;
}
