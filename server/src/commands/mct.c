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

//bct X Y q0 q1 q2 q3 q4 q5 q6\n

static int send_tile(serverdata_t *sdata, client_t *client, int x, int y)
{
    char answer[BUFFSIZE] = {0};

    sprintf(answer, "%d %d %d %d %d %d %d %d %d",
        x,
        y,
        sdata->game_data.trantor_map[x][y].resources[0],
        sdata->game_data.trantor_map[x][y].resources[1],
        sdata->game_data.trantor_map[x][y].resources[2],
        sdata->game_data.trantor_map[x][y].resources[3],
        sdata->game_data.trantor_map[x][y].resources[4],
        sdata->game_data.trantor_map[x][y].resources[5],
        sdata->game_data.trantor_map[x][y].resources[6]
    );
    send_data(client, "bct", answer, sdata->debug);
}

static int loop_send_tiles(serverdata_t *sdata, client_t *client)
{
    for (uint_t y = 0; y < sdata->args->height; y++) {
        for (uint_t x = 0; x < sdata->args->width; x++) {
            send_tile(sdata, client, x, y);
        }
    }
}

int cmd_mct(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    loop_send_tiles(sdata, client);
    return EXIT_SUCCESS;
}
