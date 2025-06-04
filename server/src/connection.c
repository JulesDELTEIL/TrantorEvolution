/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** connection.c
*/

#include "functions.h"

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
    if (client->username != NULL)
        free(client->username);
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
    int nextfree = -1;

    nextfree = getnextfree(fdarray);
    if (nextfree == -1) {
        write(2, CLIENTS_OVERFLOW_MSG, strlen(CLIENTS_OVERFLOW_MSG));
        return CLIENTS_OVERFLOW_CODE;
    }
    newfd = accept(sdata->sockfd,
            (struct sockaddr*)&sdata->address, &sdata->addrlen);
    if (newfd < 0)
        returnwitherror(ERROR_ACCEPT, EXIT_FAILURE);
    fdarray->fds[nextfree].fd = newfd;
    fdarray->clients[nextfree].fd = newfd;
    output_fd(&(fdarray->clients[nextfree]), 1, NULL, 0);
    return EXIT_SUCCESS;
}
