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
    send_data(client, "ko\n", NULL);
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

static int parse_cmd(client_t *client, char *cmd)
{
    for (uint k = 0; client->buffer[k] != 0; k++) {
        cmd[k] = client->buffer[k];
        if (client->buffer[k] == ' ')
            return k;
    }
    return -1;
}

static int parse_data(client_t *client, char *data, uint start)
{
    for (uint k = 0; client->buffer[k] != 0; k++) {
        data[k] = client->buffer[start + k];
        if (client->buffer[k] == '\n')
            return k;
    }
    return -1;
}

static int packet_parser(client_t *client, char *cmd, char *data)
{
    uint space_idx = 0;
    uint nl_idx = 0;

    if (!client || !client->buffer)
        return EXIT_FAILURE;
    space_idx = parse_cmd(client, cmd);
    if (space_idx > 0)
        nl_idx = parse_data(client, data, space_idx + 1);
    empty_client_buff(client, nl_idx);
    return EXIT_FAILURE;
    
}

int buffer_handler(serverdata_t *sdata, client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint k = 0; k < NB_USER_COMMANDS; k++) {
        if (strcmp(cmd, USER_COMMANDS[k].command) == 0)
            return USER_COMMANDS[k].handler(sdata, client, data);
    }
    handle_unrecognized_code(sdata, client);
    return EXIT_FAILURE;
}
