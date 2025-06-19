/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"

int cmd_connect_nbr(serverdata_t *sdata, client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d", client->player->team->space_left);
    send_data(client, answer, NULL, sdata->debug);
    return EXIT_SUCCESS;
}
