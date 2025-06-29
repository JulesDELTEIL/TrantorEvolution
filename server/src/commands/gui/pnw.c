/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** pnw.c
*/

#include <string.h>
#include <stdio.h>

#include "transmission.h"

int cmd_pnw(serverdata_t *sdata, fdarray_t *fdarray,
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
    sprintf(answer, "%d %d %d %d %d %s", player->id, player->pos.x,
        player->pos.y, player->orientation, player->level, player->team);
    set_message(client, "pnw", answer);
    return EXIT_SUCCESS;
}