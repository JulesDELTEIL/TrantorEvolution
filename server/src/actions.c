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
#include <string.h>

#include "commands.h"
#include "actions.h"

static int destroy_action(player_t *player)
{
    if (player->action.cmd != NULL)
        free(player->action.cmd);
    if (player->action.data != NULL)
        free(player->action.data);
    player->action.cmd = NULL;
    player->action.data = NULL;
    player->action.end = 0;
    player->action.status = DONE;
}

static int action_handler(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    int rc = DEFAULTRC;

    if (client->player->action.cmd == NULL)
        return EXIT_FAILURE;
    for (uint_t k = 0; k < NB_ACTIONS; k++) {
        if (strcmp(ACTIONS_ARR[k].name, client->player->action.cmd) == 0) {
            rc = ACTIONS_ARR[k].handler(sdata, fdarray, client,
                client->player->action.data);
            destroy_action(client->player);
            return rc;
        }
    }
}

static int check_timed_buffer(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    if (client->player == NULL)
        return EXIT_FAILURE;
    if (client->player->action.status != ONGOING) {
        return buffer_handler(sdata, fdarray, client);
    } else if (
        (tp.tv_sec * 1000 + tp.tv_usec / 1000) >= client->player->action.end) {
        action_handler(sdata, fdarray, client);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

static int check_untimed_buffer(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    if (client->buffer == NULL)
        return EXIT_FAILURE;
    return buffer_handler(sdata, fdarray, client);
}

int clients_buffers(serverdata_t *sdata, fdarray_t *fdarray)
{
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == AI)
            check_timed_buffer(sdata, fdarray, &(fdarray->clients[k]));
        else
            check_untimed_buffer(sdata, fdarray, &(fdarray->clients[k]));
    }
    return EXIT_SUCCESS;
}

