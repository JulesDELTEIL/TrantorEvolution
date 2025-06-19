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

map_t **init_map(int X, int Y)
{
    map_t **new_map = malloc(sizeof(map_t *) * (X + 1));

    for (int x = 0; x < X; x++) {
        new_map[x] = malloc(sizeof(map_t) * Y);
        for (int y = 0; y < Y; y++)
            new_map[x][y].biome = NOT_DEFINED;
    }
    new_map[X] = NULL;
    return new_map;
}
