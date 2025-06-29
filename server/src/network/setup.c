/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** setup.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "serverdata.h"
#include "fdarray.h"
#include "utils.h"
#include "map.h"

int setup_map_thread(serverdata_t *sdata, pthread_t *mapthr)
{
    pthread_create(mapthr, NULL, map_thread, sdata);
    pthread_detach(*mapthr);
    return 0;
}

serverdata_t setup_parameters(arguments_t *args)
{
    serverdata_t sdata;

    srand(time(NULL));
    sdata.debug = args->debug;
    sdata.port = args->port;
    sdata.address.sin_addr.s_addr = INADDR_ANY;
    sdata.address.sin_family = AF_INET;
    sdata.address.sin_port = htons(args->port);
    sdata.opt = 1;
    sdata.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sdata.addrlen = sizeof(sdata.address);
    sdata.game_data = init_game(args);
    sdata.is_running = true;
    return sdata;
}

int setup_server(serverdata_t *sdata, arguments_t *args)
{
    int rc = DEFAULTRC;

    rc = setsockopt(sdata->sockfd, SOL_SOCKET, SO_REUSEADDR,
        &sdata->opt, sizeof(sdata->opt));
    if (rc < 0)
        return returnwitherror(ERROR_SETSOCKOPT, EXIT_FAILURE);
    rc = bind(sdata->sockfd, (struct sockaddr*)
        &sdata->address, sdata->addrlen);
    if (rc < 0)
        return returnwitherror(ERROR_BIND, EXIT_FAILURE);
    sdata->args = args;
    return EXIT_SUCCESS;
}

int setempty_client(client_t *client)
{
    client->fd = NOFD;
    client->type = UNSET;
    client->buffin = NULL;
    client->player = NULL;
    client->buffout = NULL;
    client->buffin_addition = false;
}

fdarray_t setup_fds(int sockfd)
{
    fdarray_t fdarray;

    for (size_t k = 0; k < NBTOTAL_FD; k++) {
        fdarray.fds[k].events = POLLIN | POLLOUT;
        fdarray.fds[k].revents = 0;
        fdarray.fds[k].fd = NOFD;
        setempty_client(&(fdarray.clients[k]));
    }
    fdarray.fds[SERVER_FD_INDEX].fd = sockfd;
    fdarray.fds[SERVER_STDIN_INDEX].fd = 0;
    return fdarray;
}
