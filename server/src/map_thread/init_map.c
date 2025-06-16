/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** init_map
*/

#include <stdlib.h>
#include <unistd.h>
#include "map.h"

map_t **init_map(int X, int Y)
{
    map_t **new_map = malloc(sizeof(map_t *) * X);

    for (int i = 0; new_map[i] != NULL; i++) {
        new_map[i] = malloc(sizeof(map_t) * Y);
    }
    return new_map;
}
