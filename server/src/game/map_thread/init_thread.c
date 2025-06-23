/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** init_thread
*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "items.h"
#include "map.h"
#include "serverdata.h"

static int get_random_biome(void)
{
    return rand() % NB_BIOMES;
}

static void refill_tiles(tile_t *tile)
{
    biome_distribution_t dist;

    if (tile->biome != PLAINS)
        tile->biome = get_random_biome();
    for (int i = 0; i < NB_RESOURCES; i++)
        tile->resources[i] = 0;
    dist = biome_distributions[tile->biome];
    for (int i = 0; i < NB_RESOURCES; i++)
        tile->resources[i] = dist.biome_start[i];
}

static void first_map_refill(int Y, tile_t **map_tiles)
{
    for (int x = 0; map_tiles[x] != NULL; x++) {
        for (int y = 0; y < Y; y++) {
            refill_tiles(&map_tiles[x][y]);
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
    all_dens.dens[OIL] = map_dens * OIL_DENS;
    all_dens.dens[METAL] = map_dens * METAL_DENS;
    all_dens.dens[ANTIMATTER] = map_dens * ANTIMATTER_DENS;
    return all_dens;
}

static void *get_total(int *total, int width, int height, tile_t **tiles)
{
    int area = width * height;
    int x = 0;
    int y = 0;

    for (int i = 0; i < area; i++) {
        x = X_COORD(i, height);
        y = Y_COORD(i, height);
        for (int r = 0; r < NB_RESOURCES; r++)
            total[r] += tiles[x][y].resources[r];
    }
}

static void refill_map(tile_t **tiles, int width, int height,
    density_t *max_dens)
{
    biome_distribution_t dist = {{0}, {0}};
    int total[NB_RESOURCES] = {0, 0, 0, 0, 0, 0};
    int area = width * height;
    int x = 0;
    int y = 0;
    int add = 0;

    get_total(total, width, height, tiles);
    for (int i = 0; i < area; i++) {
        x = X_COORD(i, height);
        y = Y_COORD(i, height);
        dist = biome_distributions[tiles[x][y].biome];
        for (int r = 0; r < NB_RESOURCES; r++) {
            add = (total[r] < max_dens->dens[r])
            ? rand() % dist.refill[r] : 0;
            tiles[x][y].resources[r] += add;
            total[r] += add;
        }
    }
}

void *map_thread(void *arg)
{
    serverdata_t *server = (serverdata_t *)arg;
    density_t all_dens = init_density(WORLD_DENS(server->args));

    first_map_refill(server->args->height,
    server->game_data.map.tiles);
    while (server->is_running == true) {
        usleep(TICKS_REFILLS / server->args->freq);
        pthread_mutex_lock(&(server->game_data.map.mutex));
        refill_map(server->game_data.map.tiles, server->args->width,
        server->args->height, &all_dens);
        pthread_mutex_unlock(&(server->game_data.map.mutex));
    }
    return 0;
}
