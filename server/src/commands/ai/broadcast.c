/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** forward.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "transmission.h"
#include "commands.h"
#include "actions.h"
#include "commands/broadcast.h"

static int match_player_tile_k(player_t *player, int base_k)
{
    if (base_k < 0 || base_k > 8)
        return base_k;
    return PLAYER_DIR_INCIDENCE[player->orientation][base_k];
}

static int get_tile_k(int angle)
{
    if (angle > A_TILE_8_END || angle <= A_TILE_1_END)
        return 1;
    if (angle > A_TILE_1_END && angle <= A_TILE_2_END)
        return 2;
    if (angle > A_TILE_1_END && angle <= A_TILE_3_END)
        return 3;
    if (angle > A_TILE_1_END && angle <= A_TILE_4_END)
        return 4;
    if (angle > A_TILE_1_END && angle <= A_TILE_5_END)
        return 5;
    if (angle > A_TILE_1_END && angle <= A_TILE_6_END)
        return 6;
    if (angle > A_TILE_1_END && angle <= A_TILE_7_END)
        return 7;
    if (angle > A_TILE_1_END && angle <= A_TILE_8_END)
        return 8;
    return -1;
}

static int calculate_k(serverdata_t *sdata, client_t *sender, client_t *dest)
{
    pos_t vect;
    int angle = 0;

    if (sender->player->pos.x == dest->player->pos.x &&
        sender->player->pos.y == dest->player->pos.y)
        return 0;
    vect.x = dest->player->pos.x - sender->player->pos.x;
    vect.y = dest->player->pos.y - sender->player->pos.y;
    if (ABS(vect.x) > sdata->args->width / 2)
        vect.x = REV(vect.x, sdata->args->width);
    if (ABS(vect.y) > sdata->args->height / 2)
        vect.y = REV(vect.y, sdata->args->height);
    angle = atan2(vect.y, vect.x) * (180 / PI);
    while (angle < 0)
        angle += 360;
    angle = angle % 360;
    return match_player_tile_k(dest->player, get_tile_k(angle));
}

static int send_msg(serverdata_t *sdata, client_t *sender,
    client_t *dest, char *data)
{
    char answer[BUFSIZ] = {0};
    int k = calculate_k(sdata, sender, dest);

    sprintf(answer, "%d, %s", k, data);
    set_message(dest, "message", answer);
}

static int prepare_answer_message(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    for (uint_t k = NB_SERVER_FD; k < NBTOTAL_FD; k++) {
        if (fdarray->clients[k].type == AI &&
            (fdarray->clients[k].player->id != client->player->id))
            send_msg(sdata, client, &(fdarray->clients[k]), data);
    }
}

static void send_gui_p_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *msg)
{
    char data[BUFFSIZE] = {0};

    sprintf(data, "%d %s",
        client->player->id,
        msg
    );
    send_guis(sdata, fdarray, "pbc", data);
}

int action_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    prepare_answer_message(sdata, fdarray, client, data);
    set_message(client, "ok", NULL);
    send_gui_p_broadcast(sdata, fdarray, client, data);
}

int cmd_broadcast(serverdata_t *sdata, fdarray_t *fdarray,
    client_t *client, char *data)
{
    if (strlen(data) == 0) {
        set_message(client, "ko", NULL);
        return EXIT_FAILURE;
    }
    client->player->action.cmd = strdup(ACTIONS_ARR[BROADCAST].name);
    client->player->action.data = strdup(data);
    client->player->action.status = ONGOING;
    client->player->action.end = set_timer_end(sdata->args->freq,
        ACTIONS_ARR[BROADCAST].delay);
    return EXIT_SUCCESS;
}
