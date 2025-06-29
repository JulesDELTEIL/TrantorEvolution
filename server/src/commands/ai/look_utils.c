/*
** EPITECH PROJECT, 2024
** backup_refacto
** File description:
** utils.c
*/

#include "actions.h"

int keep_on_map(int max_val, int val)
{
    if (val < 0)
        val = (val + max_val);
    if (val >= max_val)
        val = (val - max_val);
    return val;
}

pos_t get_map_coor(serverdata_t *sdata, pos_t player_pos, pos_t vect)
{
    pos_t res;

    res.x = player_pos.x + vect.x;
    res.y = player_pos.y + vect.y;
    res.x = keep_on_map(sdata->args->width, res.x);
    res.y = keep_on_map(sdata->args->height, res.y);
    return res;
}

int get_nb_tile_players(serverdata_t *sdata, pos_t tilepos)
{
    player_t *head = sdata->game_data.players;
    int res = 0;

    while (head != NULL) {
        if (head->pos.x == tilepos.x && head->pos.y == tilepos.y)
            res++;
        head = head->next;
    }
    return res;
}
