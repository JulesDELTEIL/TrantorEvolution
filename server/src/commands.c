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

static void handle_unrecognized_code(serverdata_t *sdata, client_t *client)
{
    send_data(client, "wrc", NULL);
}

static int empty_client_buff(client_t *client, uint index)
{
    uint remaining = strlen(client->buffer) - (index + 1);
    char *newbuff = NULL;
    uint flw = 0;

    if (remaining == 0) {
        free(client->buffer);
        client->buffer = NULL;
        return EXIT_FAILURE;
    }
    newbuff = malloc(sizeof(char) * (remaining + 1));
    for (uint k = index + 1; k < remaining; k++) {
        newbuff[flw] = client->buffer[k];
        flw++;
    }
    free(client->buffer);
    client->buffer = newbuff;
    return EXIT_SUCCESS;
}

static int command_parser(client_t *client, char *dest)
{
    if (!client)
        return EXIT_FAILURE;
    if (!client->buffer)
        return EXIT_FAILURE;
    for (uint k = 0; client->buffer[k] != 0; k++) {
        dest[k] = client->buffer[k];
        if (client->buffer[k] == '\n') {
            empty_client_buff(client, k);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int command_handler(serverdata_t *sdata, client_t *client)
{
    char data[BUFFSIZE] = {0};

    if (command_parser(client, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint k = 0; k < NB_USER_COMMANDS; k++) {
        if (USER_COMMANDS[k].command[0] == data[0] &&
            USER_COMMANDS[k].command[1] == data[1] &&
            USER_COMMANDS[k].command[2] == data[2])
            return USER_COMMANDS[k].handler(sdata, client, data);
    }
    handle_unrecognized_code(sdata, client);
    return EXIT_FAILURE;
}
