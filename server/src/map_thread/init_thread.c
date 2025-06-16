/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** init_thread
*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "items.h"
#include "map.h"
#include "serverdata.h"

#include <stdlib.h>
#include <time.h>

static int get_random_biome(void)
{
    return rand() % 5;
}

static void refill_tiles(map_t tile)
{
    biome_distribution_t dist;

    tile.biome = get_random_biome();
    for (int i = 0; i < NB_RESOURCES; i++)
        tile.resources[i] = 0;
    dist = biome_distributions[tile.biome];
    for (int i = 0; i < NB_RESOURCES; i++)
        tile.resources[i] = dist.biome_start[i];
}

static void first_map_refill(int Y, density_t all_dens, map_t **map_tiles)
{
    for (int x = 0; map_tiles[x] != NULL; x++) {
        for (int y = 0; y <= Y; y++) {
            refill_tiles(map_tiles[x][y]);
        }
    }
}

static density_t init_density(int map_dens)
{
    density_t all_dens;

    all_dens.dens[FOOD] = map_dens * FOOD_DENS;
    all_dens.dens[WOOD] = map_dens * WOOD_DENS;
    all_dens.dens[ROCK] = map_dens * ROCK_DENS;
    all_dens.dens[CLAY] = map_dens * CLAY_DENS;
    all_dens.dens[PETROL] = map_dens * PETROL_DENS;
    all_dens.dens[METAL] = map_dens * METAL_DENS;
    all_dens.dens[ANTIMATTER] = map_dens * ANTIMATTER_DENS;
    return all_dens;
}

void *map_thread(void *arg)
{
    serverdata_t *server = (serverdata_t *)arg;
    int map_max_density = WORLD_DENS(server->args);
    density_t all_dens = init_density(map_max_density);

    first_map_refill(server->args->width,
    all_dens,
    server->game_data.trantor_map);
}
