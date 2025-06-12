/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-jetpack-baptiste.dunes
** File description:
** commands.c
*/

#include <stdio.h>
#include <unistd.h>

#include "commands.h"
#include "functions.h"

static void handle_unrecognized_code(serverdata_t *sdata, client_t *client,
    void *db)
{
    send_data(client, WRC, NULL, 0);
}

int command_handler(serverdata_t *sdata, client_t *client,  char *command)
{
    for (uint k = 0; k < NB_USER_COMMANDS; k++) {
        if (USER_COMMANDS[k].command[0] == command[0] &&
            USER_COMMANDS[k].command[1] == command[1] &&
            USER_COMMANDS[k].command[2] == command[2])
            return USER_COMMANDS[k].handler(sdata, client, k);
    }
    handle_unrecognized_code(sdata, client, NULL);
    return EXIT_FAILURE;
}
