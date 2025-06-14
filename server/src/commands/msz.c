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

int cmd_msz(serverdata_t *sdata, client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    sprintf(answer, "%d %d", sdata->args->width, sdata->args->height);
    send_data(client, "msz", answer);
    return EXIT_SUCCESS;
}
