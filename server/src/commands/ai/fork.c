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

static int add_egg(player_t *player)
{
    egg_t *new = malloc(sizeof(egg_t));

    new->pos = player->pos;
    new->next = player->team->eggs;
    player->team->eggs = new;
    return EXIT_SUCCESS;
}

int cmd_fork(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    add_egg(client->player);
    client->player->team->space_left++;
    set_action_end(client, sdata->args->freq, 42);
    send_data(client, "ok", NULL, sdata->debug);
    return EXIT_SUCCESS;
}
