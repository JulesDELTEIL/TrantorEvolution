/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** actions.c
*/

#include "functions.h"
#include "commands.h"
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

int input_fd(serverdata_t *sdata, client_t *client)
{
    uint8_t bytecode = 0;
    int rc = DEFAULTRC;

    rc = read(client->fd, &bytecode, 1);
    if (rc == 0) {
        printf("CL%-3d ↓  [2]\n", client->fd);
        return closeconnection(sdata, client);
    }
    printf("CL%-3d ↓  [%d]\n", client->fd, bytecode);
    return process_handler(sdata, client, bytecode);
}

int send_data(client_t *client, const uint8_t *cmd, uint8_t *data, size_t datalen)
{
    uint packetlen = PREAMBLE_LEN + SIZEINFO_LEN + CMD_LEN + datalen;
    uint8_t fullpacket[packetlen];
    int rc = DEFAULTRC;

    printf("packetlen = %d\n", packetlen);
    if (cmd == NULL)
        return EXIT_FAILURE;
    for (size_t k = 0; k < packetlen; k++)
        fullpacket[k] = 0;
    fullpacket[SIZEINFO_BEGIN_IDX] = CMD_LEN + datalen;
    for (uint k = 0; k < CMD_LEN; k++)
        fullpacket[CMD_BEGIN_IDX + k] = cmd[k];
    for (size_t k = 1; k < datalen; k++)
        fullpacket[DATA_BEGIN_IDX + k] = data[k];
    rc = write(client->fd, fullpacket, datalen + 1);
    debug_output(client, fullpacket, packetlen);
    return rc;
}
