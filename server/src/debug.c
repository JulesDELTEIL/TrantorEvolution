/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** debug.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fdarray.h"

void displayfds(fdarray_t *fdarray)
{
    printf("[");
    printf("%d", fdarray->clients[0].fd);
    for (int k = 1; k < NBTOTAL_FD; k++)
        printf(", %d", fdarray->clients[k].fd);
    printf("]\n");
}

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

void debug_buffer(client_t *client)
{
    uint_t size = 0;

    if (client->buffer == NULL) {
        printf("Cfd%-3d.buff = %dB NULL\n", client->fd, size);
        return;
    }
    size = strlen(client->buffer);
    if (size == 0) {
        printf("Cfd%-3d.buff = %dB []\n", client->fd, size);
    } else {
        printf("Cfd%-3d.buff = %dB [%d", client->fd, size, client->buffer[0]);
        for (size_t k = 1; k < size; k++)
            printf(", %d", client->buffer[k]);
        printf("]\n");
    }
}
