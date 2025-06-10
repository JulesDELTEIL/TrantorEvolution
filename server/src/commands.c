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

int command_handler(serverdata_t *sdata, client_t *client, uint8_t *command)
{
    for (uint k = 0; k < NB_COMMANDS; k++) {
        if (user_commands[k].command[0] == command[0] &&
            user_commands[k].command[1] == command[1] &&
            user_commands[k].command[2] == command[2])
            return user_commands[k].handler(sdata, client);
    }
    handle_unrecognized_code(sdata, client, NULL);
    return EXIT_FAILURE;
}
