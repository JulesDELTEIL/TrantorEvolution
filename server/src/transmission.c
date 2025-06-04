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

void debug_output(uint8_t *data, int size)
{
    if (size == 0 || !data)
        return;
    printf("↑ [%d", data[0]);
    for (size_t k = 1; k < size; k++) {
        printf(", %d", data[k]);
    }
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

int output_fd(client_t *client, uint8_t code, void *data, size_t datalen)
{
    uint8_t fullpacket[datalen + 1];
    int rc = DEFAULTRC;

    for (size_t k = 0; k < datalen + 1; k++)
        fullpacket[k] = 0;
    fullpacket[0] = code;
    if (data != NULL)
        memcpy(fullpacket + 1, &data, datalen);
    printf("CL%-3d  ↑ [%d", client->fd, fullpacket[0]);
    for (size_t k = 1; k < datalen + 1; k++)
        printf(",%d", fullpacket[k]);
    printf("]\n");
    rc = write(client->fd, fullpacket, datalen + 1);
    debug_output((uint8_t *)data, datalen);
    return rc;
}
