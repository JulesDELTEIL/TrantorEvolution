/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** debug.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "fdarray.h"

static bool is_drawable(char c)
{
    if (c < 32)
        return false;
    return true;
}

void displayfds(fdarray_t *fdarray)
{
    printf("poll : [");
    printf("%d", fdarray->fds[0].fd);
    for (int k = 1; k < NBTOTAL_FD; k++)
        printf(", %d", fdarray->fds[k].fd);
    printf("]\n");
    printf("clients : [");
    printf("%d", fdarray->clients[0].fd);
    for (int k = 1; k < NBTOTAL_FD; k++)
        printf(", %d", fdarray->clients[k].fd);
    printf("]\n");
}

void debug_input(client_t *client, char *data, int size)
{
    if (size == 0 || !data)
        return;
    if (is_drawable(data[0]))
        printf("Cfd%-3d ↓  %dB ['%c'", client->fd, size, data[0]);
    else
        printf("Cfd%-3d ↓  %dB [%d", client->fd, size, data[0]);
    for (size_t k = 1; k < size; k++) {
        if (is_drawable(data[k]))
            printf(", '%c'", data[k]);
        else
            printf(", %d", data[k]);
    }
    printf("]\n");
}

void debug_output(client_t *client, char *data, int size)
{
    if (size == 0 || !data)
        return;
    if (is_drawable(data[0]))
        printf("Cfd%-3d  ↑ %dB ['%c'", client->fd, size, data[0]);
    else
        printf("Cfd%-3d  ↑ %dB [%d", client->fd, size, data[0]);
    for (size_t k = 1; k < size; k++) {
        if (is_drawable(data[k]))
            printf(", '%c'", data[k]);
        else
            printf(", %d", data[k]);
    }
    printf("]\n");
}

void debug_buffer(client_t *client)
{
    uint_t size = 0;

    if (client->buffin == NULL || strlen(client->buffin) == 0) {
        printf("Cfd%-3d.buff = %dB []\n", client->fd, size);
        return;
    }
    size = strlen(client->buffin);
    if (is_drawable(client->buffin[0]))
        printf("Cfd%-3d.buff = %dB ['%c'", client->fd, size,
            client->buffin[0]);
    else
        printf("Cfd%-3d.buff = %dB [%d", client->fd, size, client->buffin[0]);
    for (size_t k = 1; k < size; k++) {
        if (is_drawable(client->buffin[k]))
            printf(", '%c'", client->buffin[k]);
        else
            printf(", %d", client->buffin[k]);
    }
    printf("]\n");
}
