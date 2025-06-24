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

int cmd_sst(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;
    int new_freq = 0;

    if (strlen(data) == 0) {
        send_data(client, "sbp", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    new_freq = atoi(data);
    if (new_freq == 0) {
        send_data(client, "sbp", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    sdata->args->freq = new_freq;
    sprintf(answer, "%d", sdata->args->freq);
    send_data(client, "sst", answer, sdata->debug);
    return EXIT_SUCCESS;
}
