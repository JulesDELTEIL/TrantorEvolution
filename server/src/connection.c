/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** connection.c
*/

#include "functions.h"
#include "commands.h"

static void displayfds(fdarray_t *fdarray)
{
    printf("[");
    printf("%d", fdarray->clients[0].fd);
    for (int k = 1; k < NBTOTAL_FD; k++)
        printf(", %d", fdarray->clients[k].fd);
    printf("]\n");
}

static int getnextfree(fdarray_t *fdarray)
{
    for (size_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        if (fdarray->clients[k].fd == NOFD)
            return k;
    return -1;
}

static int destroy_client(client_t *client)
{
}

int closeconnection(serverdata_t *sdata, client_t *client)
{
    close(client->fd);
    destroy_client(client);
    setempty_client(client);
    return EXIT_SUCCESS;
}

int openconnection(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;
    int newfd = NOFD;
    int nextfree = NOFD;

    nextfree = getnextfree(fdarray);
    if (nextfree == NOFD) {
        send_data(&(fdarray->clients[nextfree]), "cno", NULL);
        return CLIENTS_OVERFLOW_CODE;
    }
    newfd = accept(sdata->sockfd,
            (struct sockaddr*)&sdata->address, &sdata->addrlen);
    if (newfd < 0)
        returnwitherror(ERROR_ACCEPT, EXIT_FAILURE);
    fdarray->fds[nextfree].fd = newfd;
    fdarray->clients[nextfree].fd = newfd;
    send_data(&(fdarray->clients[nextfree]), "cye", NULL);
    return EXIT_SUCCESS;
}
