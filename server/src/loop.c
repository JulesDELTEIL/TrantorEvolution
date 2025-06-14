/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** main.c
*/

#include "functions.h"
#include "macros.h"

int search_events(serverdata_t *sdata, fdarray_t *fdarray, int k)
{
    if (fdarray->clients[k].fd == NOFD)
        return EXIT_SUCCESS;
    if (fdarray->fds[k].revents & POLLIN)
        receive_data(sdata, &(fdarray->clients[k]));
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
    int nbfds = getnb_fd(fdarray);

    if (nbfds < NB_SERVER_FD)
        return EXIT_FAILURE;
    rc = poll(fdarray->fds, nbfds, POLLTIMEOUT);
    if (rc < 0)
        return returnwitherror(ERROR_POLL, EXIT_FAILURE);
    else if (rc == 0)
        return EXIT_SUCCESS;
    if (fdarray->fds[SERVER_FD_INDEX].revents & POLLIN)
        openconnection(sdata, fdarray);
    if (fdarray->fds[SERVER_STDIN_INDEX].revents & POLLIN && check_stdin())
        return CLOSE_PROCESS;
    for (size_t k = NB_SERVER_FD; k < nbfds; k++)
        search_events(sdata, fdarray, k);
    return EXIT_SUCCESS;
}

int server_loop(arguments_t *args)
{
    serverdata_t sdata = setup_parameters(args);
    bool run = true;
    fdarray_t fdarray;
    int rc = DEFAULTRC;

    rc = setup_server(&sdata, args);
    if (rc == EXIT_FAILURE)
        return EXIT_FAILURE;
    fdarray = setup_fds(sdata.sockfd);
    listen(sdata.sockfd, NBCLIENTS_QUEUE);
    while (run) {
        rc = listen_fds(&sdata, &fdarray);
        if (rc == EXIT_FAILURE || rc == CLOSE_PROCESS)
            run = false;
    }
    close_server(&sdata, &fdarray);
    if (rc == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
