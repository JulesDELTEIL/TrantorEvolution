/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** check_clients.c
*/

#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "actions.h"
#include "functions.h"

int check_clients(serverdata_t *sdata, fdarray_t *fdarray)
{
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].fd == NOFD)
            continue;
        if (fdarray->clients[k].type == AI)
            check_ai_client(sdata, fdarray, &(fdarray->clients[k]));
        if (fdarray->clients[k].type == GUI)
            check_gui_client(sdata, fdarray, &(fdarray->clients[k]));
        if (fdarray->clients[k].type == UNSET)
            check_unknown_client(sdata, fdarray, &(fdarray->clients[k]));
    }
    return EXIT_SUCCESS;
}
