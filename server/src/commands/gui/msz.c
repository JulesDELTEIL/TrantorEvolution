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

int cmd_msz(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d %d", sdata->args->width, sdata->args->height);
    set_message(client, "msz", answer, sdata->debug);
    return EXIT_SUCCESS;
}
