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

    for (int i = 0; i < X; i++) {
        new_map[i] = malloc(sizeof(map_t) * Y);
    }
    new_map[X] = NULL;
    return new_map;
}
