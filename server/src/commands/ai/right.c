/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** forward.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "transmission.h"
#include "commands.h"

static void rotate_player(player_t *player)
{
    player->orientation -= 1;

    if (player->orientation < N)
        player->orientation = W;
}

int cmd_right(serverdata_t *sdata, client_t *client, char *data)
{
    int rc = DEFAULTRC;

    if (strlen(data) != 0) {
        send_data(client, "ko", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    rotate_player(client->player);
    set_action_end(client, sdata->args->freq, 7);
    send_data(client, "ok", NULL, sdata->debug);
    return EXIT_SUCCESS;
}
