/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

static int send_gui_fork_end(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, egg_t *new)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %d %d %d",
        new->id,
        client->player->id,
        client->player->pos.x,
        client->player->pos.y
    );
    send_guis(sdata, fdarray, M_ENW, data);
}

static int send_gui_fork_start(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d", client->player->id);
    send_guis(sdata, fdarray, M_PFK, data);
}

static int add_egg(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client)
{
    egg_t *new = malloc(sizeof(egg_t));

    if (!new)
        return EXIT_FAILURE;
    new->id = sdata->game_data.next_egg;
    sdata->game_data.next_egg++;
    new->pos = client->player->pos;
    new->next = client->player->team->eggs;
    client->player->team->eggs = new;
    send_gui_fork_end(sdata, fdarray, client, new);
    return EXIT_SUCCESS;
}

// ACTION
int action_fork(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (add_egg(sdata, fdarray, client) == EXIT_FAILURE) {
        set_message(client, M_KO, NULL);
        return EXIT_FAILURE;
    }
    client->player->team->space_left++;
    set_message(client, M_OK, NULL);
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_fork(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, M_KO, NULL);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[FORK].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[FORK].delay);
    send_gui_fork_start(sdata, fdarray, client);
    return EXIT_SUCCESS;
}
