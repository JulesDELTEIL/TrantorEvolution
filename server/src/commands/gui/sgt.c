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

int cmd_sgt(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        set_message(client, M_SBP, NULL);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d", sdata->args->freq);
    set_message(client, M_SGT, answer);
    return EXIT_SUCCESS;
}
