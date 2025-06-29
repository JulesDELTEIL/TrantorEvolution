/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** bct.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"

static int send_tile(serverdata_t *sdata, client_t *client, int x, int y)
{
    char answer[BUFFSIZE] = {0};

    sprintf(answer, "%d %d %d",
        x,
        y,
        sdata->game_data.map.tiles[x][y].biome
    );
    set_message(client, M_BIO, answer);
}

static int loop_send_tiles(serverdata_t *sdata, client_t *client)
{
    for (uint_t y = 0; y < sdata->args->height; y++) {
        for (uint_t x = 0; x < sdata->args->width; x++) {
            send_tile(sdata, client, x, y);
        }
    }
}

int cmd_bio(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        set_message(client, M_KO, NULL);
        return EXIT_FAILURE;
    }
    loop_send_tiles(sdata, client);
    return EXIT_SUCCESS;
}
