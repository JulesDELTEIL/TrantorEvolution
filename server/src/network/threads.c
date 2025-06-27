/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** threads.c
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

static int search_write_events(serverdata_t *sdata, fdarray_t *fdarray, int k)
{
    if (fdarray->clients[k].fd == NOFD)
        return EXIT_SUCCESS;
    if (!(fdarray->outfds[k].revents & POLLOUT))
        return EXIT_FAILURE;
    pthread_mutex_lock(&(fdarray->clients[k].buffout_mutex));
    if (fdarray->clients[k].buffout != NULL)
        send_data(&(fdarray->clients[k]), sdata->debug);
    pthread_mutex_unlock(&(fdarray->clients[k].buffout_mutex));
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

static int write_fds(serverdata_t *sdata, fdarray_t *fdarray)
{
    int rc = DEFAULTRC;

    rc = poll(fdarray->outfds, NBTOTAL_FD, POLLTIMEOUT);
    if (rc < 0)
        return returnwitherror(ERROR_POLL, EXIT_FAILURE);
    else if (rc == 0)
        return EXIT_SUCCESS;
    for (size_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++)
        search_write_events(sdata, fdarray, k);
    return EXIT_SUCCESS;
}

void *input_thread_loop(void *arg)
{
    thread_arg_t *shared = (thread_arg_t *)arg;
    serverdata_t *sdata = shared->sdata;
    fdarray_t *fdarray = shared->fdarray;
    int rc = DEFAULTRC;

    while (sdata->is_running) {
        rc = listen_fds(sdata, fdarray);
        if (rc == EXIT_FAILURE || rc == CLOSE_PROCESS)
            sdata->is_running = false;
    }
    free(shared);
}

void *output_thread_loop(void *arg)
{
    thread_arg_t *shared = (thread_arg_t *)arg;
    serverdata_t *sdata = shared->sdata;
    fdarray_t *fdarray = shared->fdarray;
    int rc = DEFAULTRC;

    while (sdata->is_running) {
        rc = write_fds(sdata, fdarray);
        if (rc == EXIT_FAILURE || rc == CLOSE_PROCESS)
            sdata->is_running = false;
    }
    free(shared);
}

int setup_input_thread(serverdata_t *sdata, fdarray_t *fdarray,
    pthread_t *inthr)
{
    thread_arg_t *arg = malloc(sizeof(thread_arg_t));

    arg->fdarray = fdarray;
    arg->sdata = sdata;
    pthread_create(inthr, NULL, input_thread_loop, arg);
    return 0;
}

int setup_output_thread(serverdata_t *sdata, fdarray_t *fdarray,
    pthread_t *outthr)
{
    thread_arg_t *arg = malloc(sizeof(thread_arg_t));

    arg->fdarray = fdarray;
    arg->sdata = sdata;
    pthread_create(outthr, NULL, output_thread_loop, arg);
    return 0;
}
