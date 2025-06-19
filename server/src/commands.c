/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** commands.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "debug.h"
#include "transmission.h"
#include "functions.h"

static void send_c_data_gui(serverdata_t *sdata, client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d", -1);
    send_data(client, data, NULL, sdata->debug);
    sprintf(data, "%d %d", sdata->args->width, sdata->args->height);
    send_data(client, data, NULL, sdata->debug);
}

static void send_c_data_ai(serverdata_t *sdata, client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d", client->player->team->space_left);
    send_data(client, data, NULL, sdata->debug);
    sprintf(data, "%d %d", sdata->args->width, sdata->args->height);
    send_data(client, data, NULL, sdata->debug);
}

static int set_teamname(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strcmp(data, GRAPHIC_TEAM) == 0) {
        client->type = GUI;
        send_c_data_gui(sdata, client);
        return EXIT_SUCCESS;
    }
    for (uint_t k = 0; sdata->args->team_name[k] != NULL; k++) {
        if (strcmp(data, sdata->args->team_name[k]) == 0) {
            client->type = AI;
            new_player(sdata, fdarray, client, data);
            send_c_data_ai(sdata, client);
            return EXIT_SUCCESS;
        }
    }
    send_data(client, "ko", NULL, sdata->debug);
    return EXIT_FAILURE;
}

static void handle_unrecognized_code(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    if (client->type == GUI)
        send_data(client, "suc", NULL, sdata->debug);
    else
        send_data(client, "ko", NULL, sdata->debug);
    return;
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
    for (uint_t k = index + 1; flw < remaining; k++) {
        newbuff[flw] = client->buffer[k];
        flw++;
    }
    newbuff[flw] = 0;
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

static int remove_end_spaces(char *data, int end)
{
    if (end < 0)
        return EXIT_FAILURE;
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
    int end_idx = 0;
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

int buffer_handler(serverdata_t *sdata, fdarray_t *fdarray, client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    if (client == NULL || client->buffer == NULL)
        return EXIT_FAILURE;
    if (sdata->debug)
        debug_buffer(client);
    if (packet_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (client->type == UNSET)
        return set_teamname(sdata, fdarray, client, cmd);
    for (uint_t k = 0; k < NB_COMMANDS[client->type]; k++)
        if (strcmp(cmd, COMMANDS[client->type][k].command) == 0)
            return COMMANDS[client->type][k].handler(sdata,
                fdarray, client, data);
    handle_unrecognized_code(sdata, fdarray, client);
    return EXIT_FAILURE;
}
