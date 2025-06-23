/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** loop.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "functions.h"
#include "macros.h"
#include "commands.h"
#include "transmission.h"
#include "debug.h"

int search_events(serverdata_t *sdata, fdarray_t *fdarray, int k)
{
    if (fdarray->clients[k].fd == NOFD)
        return EXIT_SUCCESS;
    if (fdarray->fds[k].revents & POLLIN)
        if (receive_data(sdata, &(fdarray->clients[k])) == CLOSE_CONNECTION)
            fdarray->fds[k].fd = NOFD;
}

static int getnb_fd(fdarray_t *fdarray)
{
    for (size_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        if (fdarray->clients[k].fd == NOFD)
            return k;
    return -1;
}

static bool check_stdin(void)
{
    char *buff = NULL;
    size_t size = 0;

    if (getline(&buff, &size, stdin) == -1) {
        free(buff);
        return true;
    }
    free(buff);
    return false;
}

int listen_fds(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;

    rc = poll(fdarray->fds, NBTOTAL_FD, POLLTIMEOUT);
    if (rc < 0)
        return returnwitherror(ERROR_POLL, EXIT_FAILURE);
    else if (rc == 0)
        return EXIT_SUCCESS;
    if (fdarray->fds[SERVER_FD_INDEX].revents & POLLIN)
        openconnection(sdata, fdarray);
    if (fdarray->fds[SERVER_STDIN_INDEX].revents & POLLIN && check_stdin())
        return CLOSE_PROCESS;
    for (size_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        search_events(sdata, fdarray, k);
    return EXIT_SUCCESS;
}

static int server_loop(serverdata_t *sdata, fdarray_t *fdarray)
{
    bool run = true;
    int rc = DEFAULTRC;

    while (run) {
        rc = listen_fds(sdata, fdarray);
        if (rc == EXIT_FAILURE || rc == CLOSE_PROCESS)
            run = false;
        clients_buffers(sdata, fdarray);
    }
    return rc;
}

int server(arguments_t *args)
{
    serverdata_t sdata = setup_parameters(args);
    pthread_t mapthr;
    fdarray_t fdarray;
    int rc = DEFAULTRC;

    rc = setup_server(&sdata, args);
    if (rc == EXIT_FAILURE)
        return EXIT_FAILURE;
    setup_map_thread(&sdata, &mapthr);
    fdarray = setup_fds(sdata.sockfd);
    listen(sdata.sockfd, NBCLIENTS_QUEUE);
    rc = server_loop(&sdata, &fdarray);
    close_server(&sdata, &fdarray, &mapthr);
    if (rc == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
