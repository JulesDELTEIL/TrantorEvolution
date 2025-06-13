/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** idn.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int cmd_idn(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (client->team != NULL) {
        send_data(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    send_data(client, "ok", NULL);
    client->team = strdup(data);
    return EXIT_SUCCESS;
}
