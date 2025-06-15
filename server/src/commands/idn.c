/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** idn.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "transmission.h"

static int set_teamname(char **args_teamnames, client_t *client, char *data)
{
    if (strcmp(data, "graphic") == 0) {
        client->team = strdup(data);
        return EXIT_SUCCESS;
    }
    for (uint_t k = 0; args_teamnames[k] != NULL; k++) {
        if (strcmp(data, args_teamnames[k]) == 0) {
            client->team = strdup(data);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int cmd_idn(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (client->team != NULL || data == NULL || strlen(data) == 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    if (set_teamname(sdata->args->team_name, client, data) == EXIT_FAILURE) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    send_data(client, "ok", NULL, sdata->debug);
    return EXIT_SUCCESS;
}
