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

static int parse_cmd(client_t *client, char *cmd, bool *nl_presence)
{
    for (uint_t k = 0; client->buffer[k] != 0; k++) {
        if (client->buffer[k] == '\n') {
            *nl_presence = true;
            return k;
        }
        if (client->buffer[k] == ' ') {
            return k;
        }
        cmd[k] = client->buffer[k];
    }
    return -1;
}

static int remove_end_spaces(char *data, uint_t end)
{
    for (uint_t k = end; k > 0; k++) {
        if (data[k] != ' ')
            return 0;
        data[k] = 0;
    }
}

static int parse_data(client_t *client, char *data, uint_t cmdend_idx,
    bool *nl_presence)
{
    uint_t flw = 0;

    if (cmdend_idx < 1 || client->buffer[cmdend_idx] != ' ')
        return cmdend_idx;
    cmdend_idx++;
    for (uint_t k = cmdend_idx; client->buffer[k] != 0; k++) {
        if (client->buffer[k] == '\n') {
            *nl_presence = true;
            remove_end_spaces(data, flw - 1);
            return k;
        }
        if (client->buffer[k] != ' ' || client->buffer[k - 1] != ' ') {
            data[flw] = client->buffer[k];
            flw++;
        }
    }
    return -1;
}

static int packet_parser(client_t *client, char *cmd, char *data)
{
    uint_t end_idx = 0;
    bool nl_presence = false;

    end_idx = parse_cmd(client, cmd, &nl_presence);
    if (end_idx <= 0)
        return EXIT_FAILURE;
    if (nl_presence == false)
        end_idx = parse_data(client, data, end_idx, &nl_presence);
    if (end_idx <= 0)
        return EXIT_FAILURE;
    empty_client_buff(client, end_idx);
    return EXIT_SUCCESS;
}

void debug_buffer(client_t *client)
{
    uint_t size = 0;

    if (client->buffer == NULL)
        return;
    size = strlen(client->buffer);
    if (size == 0) {
        printf("Cfd%-3d.buff = %dB []", client->fd, size);
    } else {
        printf("Cfd%-3d.buff = %dB [%d", client->fd, size, client->buffer[0]);
        for (size_t k = 1; k < size; k++)
            printf(", %d", client->buffer[k]);
        printf("]\n");
    }
}

int buffer_handler(serverdata_t *sdata, client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    debug_buffer(client);
    if (client == NULL)
        return EXIT_FAILURE;
    if (client->buffer == NULL)
        return EXIT_FAILURE;
    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < NB_USER_COMMANDS; k++)
        if (strcmp(cmd, USER_COMMANDS[k].command) == 0)
            return USER_COMMANDS[k].handler(sdata, client, data);
    handle_unrecognized_code(sdata, client);
    return EXIT_FAILURE;
}
