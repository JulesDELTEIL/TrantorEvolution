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

static int command_parser(client_t *client, char *cmd, char *data)
{
    uint cmdlen = 0;
    uint flw = 0;

    if (!client || !client->buffer)
        return EXIT_FAILURE;
    for (uint k = 0; client->buffer[k] != 0 && client->buffer[k] != ' '; k++) {
        cmd[k] = client->buffer[flw];
        flw++;
    }
    flw++;
    for (uint k = 0; client->buffer[flw] != 0; k++) {
        data[k] = client->buffer[flw];
        if (client->buffer[k] == '\n') {
            empty_client_buff(client, flw);
            return EXIT_SUCCESS;
        }
        flw++;
    }
    return EXIT_FAILURE;
}

static int compare_str(char *s1, char *s2)
{
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);
    int smallest_len = len_s1;

    if (len_s1 > len_s2) {
        smallest_len = len_s2;
    }
    for (int k = 0; k < smallest_len; k++) {
        if (s1[k] != s2[k]) {
            return s1[k] - s2[k];
        }
    }
    return 0;
}

int command_handler(serverdata_t *sdata, client_t *client)
{
    char cmd[BUFFSIZE] = {0};
    char data[BUFFSIZE] = {0};

    if (command_parser(client, cmd, data) == EXIT_FAILURE)
        return EXIT_FAILURE;
    for (uint k = 0; k < NB_USER_COMMANDS; k++) {
        if (compare_str(cmd, USER_COMMANDS[k].command) == 0)
            return USER_COMMANDS[k].handler(sdata, client, data);
    }
    handle_unrecognized_code(sdata, client);
    return EXIT_FAILURE;
}
