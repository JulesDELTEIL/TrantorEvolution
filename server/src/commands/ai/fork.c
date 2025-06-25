/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"

static int add_egg(player_t *player)
{
    egg_t *new = malloc(sizeof(egg_t));

    new->pos = player->pos;
    new->next = player->team->eggs;
    player->team->eggs = new;
    return EXIT_SUCCESS;
}

// ACTION
int action_fork(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    add_egg(client->player);
    client->player->team->space_left++;
    set_message(client, "ok", NULL, sdata->debug);
    return EXIT_SUCCESS;
}

// COMMAND
int cmd_fork(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) != 0) {
        set_message(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[FORK].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[FORK].delay);
    return EXIT_SUCCESS;
}
