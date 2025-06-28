/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** status
*/

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>

#include "items.h"
#include "map.h"
#include "serverdata.h"

biome_distribution_t get_first_refill_status(bool biome_active,
    tile_t *tile)
{
    if (biome_active == true) {
        return biome_distributions[tile->biome];
    }
    return normal_distributions[tile->biome];
}

biome_distribution_t get_refill_status(bool biome_active,
    int x,
    int y,
    tile_t **tiles)
{
    if (biome_active == true)
        return biome_distributions[tiles[x][y].biome];
    return normal_distributions[tiles[x][y].biome];
}
