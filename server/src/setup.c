/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** setup.c
*/

#include "functions.h"

serverdata_t setup_parameters(arguments_t *args)
{
    serverdata_t sdata;

    sdata.port = args->port;
    sdata.address.sin_addr.s_addr = INADDR_ANY;
    sdata.address.sin_family = AF_INET;
    sdata.address.sin_port = htons(args->port);
    sdata.opt = 1;
    sdata.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sdata.addrlen = sizeof(sdata.address);
    return sdata;
}

int setup_server(serverdata_t *sdata)
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
    return EXIT_SUCCESS;
}

int setempty_client(client_t *client)
{
    client->fd = NOFD;
    client->id = 0;
    client->team = NULL;
    client->buffer = NULL;
    client->type = UNSET;
    client->player.meters = 0;
    client->player.pos_x = 0;
    client->player.pos_y = 0;
    client->player.score = 0;
    client->player.speed = 0;
    client->player.status = -1;
}

fdarray_t setup_fds(int sockfd)
{
    fdarray_t fdarray;

    for (size_t k = 0; k < NBTOTAL_FD; k++) {
        fdarray.fds[k].events = POLLIN;
        fdarray.fds[k].revents = 0;
        fdarray.fds[k].fd = NOFD;
        setempty_client(&(fdarray.clients[k]));
    }
    fdarray.fds[SERVER_FD_INDEX].fd = sockfd;
    fdarray.fds[SERVER_STDIN_INDEX].fd = 0;
    return fdarray;
}
