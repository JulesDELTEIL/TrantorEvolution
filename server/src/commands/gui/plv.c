/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** idn.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "transmission.h"

int cmd_plv(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;
    player_t *player = NULL;

    if (strlen(data) == 0) {
        set_message(client, "sbp", NULL);
        return EXIT_FAILURE;
    }
    player = get_player_pos(sdata, atoi(data));
    if (player == NULL) {
        set_message(client, "sbp", NULL);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d %d", player->id, player->level);
    set_message(client, "plv", answer);
    return EXIT_SUCCESS;
}
