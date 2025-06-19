/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** connection.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"
#include "transmission.h"

static int getnextfree(fdarray_t *fdarray)
{
    for (size_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        if (fdarray->clients[k].fd == NOFD)
            return k;
    return -1;
}

int closeconnection(serverdata_t *sdata, client_t *client)
{
    close(client->fd);
    destroy_client(client);
    if (client->type == AI)
        del_player(&(sdata->game_data), client->player->id);
    setempty_client(client);
    return EXIT_SUCCESS;
}

static int set_new_client(serverdata_t *sdata, fdarray_t *fdarray,
    int nextfree, int newfd)
{
    fdarray->fds[nextfree].fd = newfd;
    fdarray->clients[nextfree].fd = newfd;
}

int openconnection(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;
    int newfd = NOFD;
    int nextfree = NOFD;

    nextfree = getnextfree(fdarray);
    if (nextfree == NOFD) {
        send_data(&(fdarray->clients[nextfree]),
            "REFUSED", NULL, sdata->debug);
        return CLIENTS_OVERFLOW_CODE;
    }
    newfd = accept(sdata->sockfd,
            (struct sockaddr*)&sdata->address, &sdata->addrlen);
    if (newfd < 0)
        returnwitherror(ERROR_ACCEPT, EXIT_FAILURE);
    set_new_client(sdata, fdarray, nextfree, newfd);
    send_data(&(fdarray->clients[nextfree]), "WELCOME", NULL, sdata->debug);
    return EXIT_SUCCESS;
}
