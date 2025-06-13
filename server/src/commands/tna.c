/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna.c
*/

#include <unistd.h>
#include <stdlib.h>

#include "structs.h"
#include "commands.h"

int cmd_tna(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    client->type = data[0];
    return EXIT_SUCCESS;
}
