/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** actions.c
*/

#include "functions.h"
#include "commands.h"

void debug_input(client_t *client, char *data, int size)
{
    if (size == 0 || !data)
        return;
    printf("Cfd%-3d ↓  %dB [%d", client->fd, size, data[0]);
    for (size_t k = 1; k < size; k++) {
        printf(", %d", data[k]);
    }
    printf("]\n");
}

void debug_output(client_t *client, char *data, int size)
{
    if (size == 0 || !data)
        return;
    printf("Cfd%-3d  ↑ %dB [%d", client->fd, size, data[0]);
    for (size_t k = 1; k < size; k++)
        printf(", %d", data[k]);
    printf("]\n");
}

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

int receive_data(serverdata_t *sdata, client_t *client)
{
    char buffer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;

    rc = read(client->fd, buffer, BUFFSIZE - 1);
    if (rc == 0) {
        printf("Cfd%-3d ↓  ✕\n", client->fd);
        return closeconnection(sdata, client);
    } else if (rc == -1)
        return EXIT_FAILURE;
    debug_input(client, buffer, rc);
    add_circular(client, buffer);
    return buffer_handler(sdata, client);
}

static int get_datalen(char *data)
{
    if (data == NULL)
        return 0;
    return strlen(data);
}

int send_data(client_t *client, char *cmd, char *data)
{
    uint_t datalen = get_datalen(data);
    uint_t cmdlen = get_datalen(cmd);
    uint_t packetlen = cmdlen + datalen + 1;
    char fullpacket[packetlen];
    int rc = DEFAULTRC;

    if (cmd == NULL)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < cmdlen; k++)
        fullpacket[k] = cmd[k];
    for (size_t k = 0; k < datalen; k++)
        fullpacket[cmdlen + k] = data[k];
    fullpacket[cmdlen + datalen] = '\n';
    rc = write(client->fd, fullpacket, packetlen);
    debug_output(client, fullpacket, packetlen);
    return rc;
}
