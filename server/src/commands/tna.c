/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int cmd_tna(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    send_data(client, "ok", NULL);
    return EXIT_SUCCESS;
}
