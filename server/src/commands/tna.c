/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "transmission.h"

int cmd_tna(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    for (uint_t k = 0; sdata->args->team_name[k]; k++) {
        send_data(client, "tna", sdata->args->team_name[k], sdata->debug);
    }
    return EXIT_SUCCESS;
}
