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
#include <unistd.h>

#include "functions.h"
#include "macros.h"
#include "commands.h"
#include "transmission.h"
#include "debug.h"

static int search_listen_events(serverdata_t *sdata, fdarray_t *fdarray, int k)
{
    if (fdarray->clients[k].fd == NOFD)
        return EXIT_SUCCESS;
    if (!(fdarray->infds[k].revents & POLLIN))
        return EXIT_FAILURE;
    if (receive_data(sdata, fdarray,
    &(fdarray->clients[k])) == CLOSE_CONNECTION) {
        fdarray->infds[k].fd = NOFD;
        fdarray->outfds[k].fd = NOFD;
    }
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

static int listen_fds(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;

    rc = poll(fdarray->infds, NBTOTAL_FD, POLLTIMEOUT);
    if (rc < 0)
        return returnwitherror(ERROR_POLL, EXIT_FAILURE);
    else if (rc == 0)
        return EXIT_SUCCESS;
    if (fdarray->infds[SERVER_FD_INDEX].revents & POLLIN)
        openconnection(sdata, fdarray);
    if (fdarray->infds[SERVER_STDIN_INDEX].revents & POLLIN && check_stdin())
        return CLOSE_PROCESS;
    for (size_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        search_listen_events(sdata, fdarray, k);
    return EXIT_SUCCESS;
}

static int server_loop(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;

    while (sdata->is_running) {
        check_clients(sdata, fdarray);
        rc = listen_fds(sdata, fdarray);
        if (rc == EXIT_FAILURE || rc == CLOSE_PROCESS)
            sdata->is_running = false;
    }
    return EXIT_SUCCESS;
}

int server(arguments_t *args)
{
    serverdata_t sdata = setup_parameters(args);
    pthread_t mapthr;
    pthread_t outthr;
    fdarray_t fdarray;
    int rc = DEFAULTRC;

    rc = setup_server(&sdata, args);
    if (rc == EXIT_FAILURE)
        return EXIT_FAILURE;
    setup_map_thread(&sdata, &fdarray, &mapthr);
    fdarray = setup_fds(sdata.sockfd);
    listen(sdata.sockfd, NBCLIENTS_QUEUE);
    setup_output_thread(&sdata, &fdarray, &outthr);
    rc = server_loop(&sdata, &fdarray);
    close_server(&sdata, &fdarray, &mapthr);
    pthread_join(outthr, NULL);
    if (rc == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
