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

player_t *get_player_pos(serverdata_t *sdata, int player_id)
{
    player_t *head = sdata->game_data.players;

    while (head != NULL) {
        if (head->id == player_id)
            return head;
        head = head->next;
    }
    return NULL;
}

int cmd_ppo(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    char answer[BUFFSIZE] = {0};
    int rc = DEFAULTRC;
    player_t *player = NULL;

    if (strlen(data) == 0) {
        send_data(client, "sbp", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    player = get_player_pos(sdata, atoi(data));
    if (player == NULL) {
        send_data(client, "sbp", NULL, sdata->debug);
        return EXIT_FAILURE;
    }
    sprintf(answer, "%d %d %d %d", player->id, player->pos.x, player->pos.y,
        player->orientation);
    send_data(client, "ppo", answer, sdata->debug);
    return EXIT_SUCCESS;
}
