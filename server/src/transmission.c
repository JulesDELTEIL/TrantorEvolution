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
    printf("C%-3d ↓ [%d", client->fd, data[0]);
    for (size_t k = 1; k < size; k++) {
        printf(", %d", data[k]);
    }
    printf("]\n");
}

void debug_output(client_t *client, uint8_t *data, int size)
{
    if (size == 0 || !data)
        return;
    printf("CL%-3d  ↑ [%d", client->fd, data[0]);
    for (size_t k = 1; k < size; k++)
        printf(",%d", data[k]);
    printf("]\n");
}

int receive_data(serverdata_t *sdata, client_t *client)
{
    uint8_t buffer[CMD_LEN] = {0};
    int rc = DEFAULTRC;

    rc = read(client->fd, buffer, CMD_LEN);
    if (rc == 0) {
        printf("CL%-3d ↓  ✕\n", client->fd);
        return closeconnection(sdata, client);
    } else if (rc == -1 || rc != CMD_LEN)
        return EXIT_FAILURE;
    debug_input(client, buffer, rc);
    return command_handler(sdata, client, buffer);
}

int send_data(client_t *client, const uint8_t *cmd, uint8_t *data, size_t datalen)
{
    uint packetlen = CMD_LEN + datalen + EOP_LEN;
    uint8_t fullpacket[packetlen];
    int rc = DEFAULTRC;

    if (cmd == NULL)
        return EXIT_FAILURE;
    for (uint k = 0; k < CMD_LEN; k++)
        fullpacket[CMD_BEGIN_IDX + k] = cmd[k];
    for (size_t k = 1; k < datalen; k++)
        fullpacket[DATA_BEGIN_IDX + k] = data[k];
    fullpacket[DATA_BEGIN_IDX + datalen] = EOP;
    rc = write(client->fd, fullpacket, datalen + 1);
    debug_output(client, fullpacket, packetlen);
    return rc;
}
