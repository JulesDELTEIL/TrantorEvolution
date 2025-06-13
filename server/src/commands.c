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
    send_data(client, "ko", NULL);
}

static int empty_client_buff(client_t *client, uint_t index)
{
    uint_t remaining = strlen(client->buffer) - (index + 1);
    char *newbuff = NULL;
    uint_t flw = 0;

    if (remaining == 0) {
        free(client->buffer);
        client->buffer = NULL;
        return EXIT_FAILURE;
    }
    newbuff = malloc(sizeof(char) * (remaining + 1));
    for (uint_t k = index + 1; k < remaining; k++) {
        newbuff[flw] = client->buffer[k];
        flw++;
    }
    free(client->buffer);
    client->buffer = newbuff;
    return EXIT_SUCCESS;
}

static int parse_cmd(client_t *client, char *cmd)
{
    for (uint_t k = 0; client->buffer[k] != 0; k++) {
        if (client->buffer[k] == ' ' || client->buffer[k] == '\n')
            return k;
        cmd[k] = client->buffer[k];
    }
    return -1;
}

static int parse_data(client_t *client, char *data, uint_t cmdend_idx)
{
    if (client->buffer[cmdend_idx] != ' ')
        return cmdend_idx;
    cmdend_idx++;
    for (uint_t k = cmdend_idx; client->buffer[k] != 0; k++) {
        data[k - cmdend_idx] = client->buffer[k];
        if (client->buffer[k] == '\n')
            return k;
    }
    return -1;
}

static int packet_parser(client_t *client, char *cmd, char *data)
{
    uint_t space_idx = 0;
    uint_t nl_idx = 0;

    space_idx = parse_cmd(client, cmd);
    if (space_idx <= 0)
        return EXIT_FAILURE;
    nl_idx = parse_data(client, data, space_idx);
    if (nl_idx > 0)
        empty_client_buff(client, nl_idx);
    return EXIT_SUCCESS;
}

static bool command_ready(client_t *client)
{
    for (uint_t k = 0; client->buffer[k] != 0; k++)
        if (client->buffer[k] == '\n')
            return true;
    return false;
}

int buffer_handler(serverdata_t *sdata, client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    if (command_ready(client) == false)
        return EXIT_FAILURE;
    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < NB_USER_COMMANDS; k++) {
        if (strcmp(cmd, USER_COMMANDS[k].command) == 0)
            return USER_COMMANDS[k].handler(sdata, client, data);
    }
    handle_unrecognized_code(sdata, client);
    return EXIT_FAILURE;
}
