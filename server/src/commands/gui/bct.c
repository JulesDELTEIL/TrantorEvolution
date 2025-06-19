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

static int fill_answer(char *answer, serverdata_t *sdata, int x, int y)
{
    sprintf(answer, "%d %d %d %d %d %d %d %d %d",
        x,
        y,
        sdata->game_data.map.tiles[x][y].resources[0],
        sdata->game_data.map.tiles[x][y].resources[1],
        sdata->game_data.map.tiles[x][y].resources[2],
        sdata->game_data.map.tiles[x][y].resources[3],
        sdata->game_data.map.tiles[x][y].resources[4],
        sdata->game_data.map.tiles[x][y].resources[5],
        sdata->game_data.map.tiles[x][y].resources[6]
    );
}

static int extract_positions(char *data, int *x, int *y)
{
    char first[32] = {0};
    char second[32] = {0};
    int flw = 0;

    for (uint_t k = 0; data[flw] != ' '; k++) {
        if (data[flw] == 0)
            return EXIT_FAILURE;
        first[k] = data[flw];
        flw++;
    }
    flw++;
    for (uint_t k = 0; data[flw] != 0; k++) {
        if (data[flw] == ' ')
            return EXIT_FAILURE;
        second[k] = data[flw];
        flw++;
    }
    *x = atoi(first);
    *y = atoi(second);
    return EXIT_SUCCESS;
}

int cmd_bct(serverdata_t *sdata, client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;
    int x = 0;
    int y = 0;

    if (strlen(data) == 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    rc = extract_positions(data, &x, &y);
    if (rc == EXIT_FAILURE || x >= sdata->args->width
        || y >= sdata->args->height || x < 0 || y < 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    fill_answer(answer, sdata, x, y);
    send_data(client, "bct", answer, sdata->debug);
    return EXIT_SUCCESS;
}
