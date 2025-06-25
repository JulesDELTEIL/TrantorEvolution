/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** send_guis.c
*/

#include "serverdata.h"
#include "fdarray.h"
#include "transmission.h"

int send_guis(serverdata_t *sdata, fdarray_t *fdarray, char *cmd, char *data)
{
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        if (fdarray->clients[k].type == GUI)
            set_message(&(fdarray->clients[k]), cmd, data, sdata->debug);
}
