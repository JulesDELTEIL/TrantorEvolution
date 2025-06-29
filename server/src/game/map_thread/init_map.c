/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** init_map
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "map.h"

static void *cancel_map_init(tile_t **map, int now)
{
    for (unsigned int k = 0; k < now; k++)
        free(map[k]);
    free(map);
    return NULL;
}

tile_t **init_map(int X, int Y)
{
    tile_t **new_map = malloc(sizeof(tile_t *) * (X + 1));

    if (!new_map)
        return NULL;
    for (int x = 0; x < X; x++) {
        new_map[x] = malloc(sizeof(tile_t) * Y);
        if (!new_map[x])
            return cancel_map_init(new_map, x);
        for (int y = 0; y < Y; y++)
            new_map[x][y].biome = NOT_DEFINED;
    }
    new_map[X] = NULL;
    return new_map;
}
