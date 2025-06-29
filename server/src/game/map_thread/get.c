/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** init_thread
*/

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>

#include "items.h"
#include "map.h"
#include "serverdata.h"

int get_biome(double noise)
{
    if (noise <= SEA_NOISE)
        return SEA;
    if (noise <= BEACH_NOISE)
        return BEACH;
    if (noise <= PLAINS_NOISE)
        return PLAINS;
    if (noise <= FOREST_NOISE)
        return FOREST;
    return MOUNTAINS;
}

int get_spawn_biome(float noise)
{
    if (noise <= BEACH_NOISE)
        return BEACH;
    if (noise <= PLAINS_NOISE)
        return PLAINS;
    if (noise <= FOREST_NOISE)
        return FOREST;
    return MOUNTAINS;
}
