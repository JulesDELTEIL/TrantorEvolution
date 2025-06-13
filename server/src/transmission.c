/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** actions.c
*/

#include "functions.h"
#include "commands.h"

void debug_input(client_t *client, uint8_t *data, int size)
{
    if (size == 0 || !data)
        return;
    printf("C%-3d ↓ [%s]\n", client->fd, data);
}

void debug_output(client_t *client, uint8_t *data, int size)
{
    if (size == 0 || !data)
        return;
    printf("CL%-3d  ↑ [%s]\n", client->fd, data);
}

static int add_circular(client_t *client, char *buffer)
{
    char *newbuff = NULL;
    uint c_bufflen = 0;
    uint n_bufflen = strlen(buffer);

    if (client->buffer != NULL)
        c_bufflen = strlen(client->buffer);
    newbuff = malloc(sizeof(char) * (c_bufflen + n_bufflen + 1));
    for (uint k = 0; k < c_bufflen; k++)
        newbuff[k] = client->buffer[k];
    for (uint k = 0; k < n_bufflen; k++)
        newbuff[k + c_bufflen] = buffer[k];
    newbuff[c_bufflen + n_bufflen] = 0;
    if (client->buffer != NULL)
        free(client->buffer);
    client->buffer = newbuff;
    return EXIT_SUCCESS;
}

int receive_data(serverdata_t *sdata, client_t *client)
{
    char buffer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    rc = read(client->fd, buffer, BUFFSIZE - 1);
    if (rc == 0) {
        printf("CL%-3d ↓  ✕\n", client->fd);
        return closeconnection(sdata, client);
    } else if (rc == -1)
        return EXIT_FAILURE;
    debug_input(client, buffer, rc);
    add_circular(client, buffer);
    return command_handler(sdata, client);
}

static int get_datalen(char *data)
{
    if (data == NULL)
        return 0;
    return strlen(data);
}

int send_data(client_t *client, char *cmd, char *data)
{
    uint datalen = get_datalen(data);
    uint cmdlen = get_datalen(cmd);
    uint packetlen = cmdlen + datalen + 1;
    uint8_t fullpacket[packetlen];
    int rc = DEFAULTRC;

    if (cmd == NULL)
        return EXIT_FAILURE;
    for (uint k = 0; k < cmdlen; k++)
        fullpacket[k] = cmd[k];
    for (size_t k = 0; k < datalen; k++)
        fullpacket[cmdlen + k] = data[k];
    fullpacket[cmdlen + datalen] = '\n';
    rc = write(client->fd, fullpacket, datalen + 1);
    debug_output(client, fullpacket, packetlen);
    return rc;
}
