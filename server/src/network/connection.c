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

static int destroy_buffout(message_t *head)
{
    message_t *temp = NULL;

    while (head != NULL) {
        temp = head->next;
        free(head->data);
        free(head);
        head = temp;
    }
}

int closeconnection(serverdata_t *sdata, fdarray_t *fdarray, client_t *client)
{
    printf("\033[34mDisconnection from client fd %d\033[0m\n", client->fd); // COMMENT TO REMEMBER TO REMOVE
    if (client->type == AI) { // COMMENT TO REMEMBER TO REMOVE
        printf("\033[34mClient %d was linked to player %d, killing it\033[0m\n", client->fd, client->player->id); // COMMENT TO REMEMBER TO REMOVE
    } // COMMENT TO REMEMBER TO REMOVE
    close(client->fd);
    destroy_client(client);
    if (client->type == AI)
        kill_player(sdata, fdarray, client);
    destroy_buffout(client->buffout);
    setempty_client(client);
    return CLOSE_CONNECTION;
}

static int set_new_client(serverdata_t *sdata, fdarray_t *fdarray,
    int nextfree, int newfd)
{
    fdarray->fds[nextfree].fd = newfd;
    fdarray->clients[nextfree].fd = newfd;
    printf("\033[34mConnection from client %d at idx %d\033[0m\n", newfd, nextfree); // COMMENT TO REMEMBER TO REMOVE
}

int openconnection(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;
    int newfd = NOFD;
    int nextfree = NOFD;

    nextfree = getnextfree(fdarray);
    if (nextfree == NOFD)
        return CLIENTS_OVERFLOW_CODE;
    newfd = accept(sdata->sockfd,
            (struct sockaddr*)&sdata->address, &sdata->addrlen);
    if (newfd < 0)
        returnwitherror(ERROR_ACCEPT, EXIT_FAILURE);
    set_new_client(sdata, fdarray, nextfree, newfd);
    set_message(&(fdarray->clients[nextfree]), "WELCOME", NULL);
    return EXIT_SUCCESS;
}
