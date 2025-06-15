/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** actions.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "functions.h"
#include "debug.h"

static int add_circular(client_t *client, char *buffer)
{
    char *newbuff = NULL;
    uint_t c_bufflen = 0;
    uint_t n_bufflen = strlen(buffer);

    if (client->buffer != NULL)
        c_bufflen = strlen(client->buffer);
    newbuff = malloc(sizeof(char) * (c_bufflen + n_bufflen + 1));
    for (uint_t k = 0; k < c_bufflen; k++)
        newbuff[k] = client->buffer[k];
    for (uint_t k = 0; k < n_bufflen; k++)
        newbuff[k + c_bufflen] = buffer[k];
    newbuff[c_bufflen + n_bufflen] = 0;
    if (client->buffer != NULL)
        free(client->buffer);
    client->buffer = newbuff;
    return EXIT_SUCCESS;
}

static int count_nl(char *buff)
{
    int count = 0;

    if (buff == NULL)
        return 0;
    for (uint_t k = 0; buff[k] != 0; k++)
        if (buff[k] == '\n')
            count++;
    return count;
}

int receive_data(serverdata_t *sdata, client_t *client)
{
    char buffer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    rc = read(client->fd, buffer, BUFFSIZE - 1);
    if (rc == 0) {
        if (sdata->debug)
            printf("Cfd%-3d ↓  ✕\n", client->fd);
        return closeconnection(sdata, client);
    } else if (rc == -1)
        return EXIT_FAILURE;
    if (sdata->debug)
        debug_input(client, buffer, rc);
    if (rc < 2 || count_nl(client->buffer) >= 10)
        return EXIT_FAILURE;
    add_circular(client, buffer);
    return EXIT_SUCCESS;
}

static int get_datalen(char *data)
{
    if (data == NULL)
        return 0;
    return strlen(data);
}

int send_data(client_t *client, char *cmd, char *data, bool debug)
{
    uint_t datalen = get_datalen(data);
    uint_t cmdlen = get_datalen(cmd);
    uint_t packetlen = cmdlen + 1 + datalen + 1;
    char fullpacket[packetlen];
    int rc = DEFAULTRC;

    if (cmd == NULL)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < cmdlen; k++)
        fullpacket[k] = cmd[k];
    fullpacket[cmdlen] = ' ';
    for (size_t k = 0; k < datalen; k++)
        fullpacket[cmdlen + 1 + k] = data[k];
    fullpacket[cmdlen + 1 + datalen] = '\n';
    rc = write(client->fd, fullpacket, packetlen);
    if (debug)
        debug_output(client, fullpacket, packetlen);
    return rc;
}
