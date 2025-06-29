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

static void refill_tiles(tile_t *tile, bool biome_active)
{
    biome_distribution_t dist;

    if (tile->biome != PLAINS) {
        tile->biome = get_biome(tile->noise);
    } else {
        tile->biome = get_spawn_biome(tile->noise);
    }
    for (int i = 0; i < NB_RESOURCES; i++)
        tile->resources[i] = 0;
    dist = get_first_refill_status(biome_active, tile);
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (biome_active == false) {
            tile->resources[i] = rand() % dist.biome_start[i];
            continue;
        }
        tile->resources[i] = dist.biome_start[i];
    }
}

static void first_map_refill(int Y, tile_t **map_tiles, bool biome_active)
{
    for (int x = 0; map_tiles[x] != NULL; x++) {
        for (int y = 0; y < Y; y++) {
            refill_tiles(&map_tiles[x][y], biome_active);
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

static void get_total(int *total, int width, int height, tile_t **tiles)
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

static void create_shuffled_indices(int *shuffle, int area)
{
    int new_value = 0;
    int tmp = 0;


    for (int i = 0; i < area; i++)
        shuffle[i] = i;
    for (int i = area - 1; i > 0; i--) {
        new_value = rand() % (i + LAST_VALUE);
        tmp = shuffle[i];
        shuffle[i] = shuffle[new_value];
        shuffle[new_value] = tmp;
    }
}

static void refill_tile_resources(tile_t *tile,
    biome_distribution_t dist,
    int *total,
    density_t *max_dens)
{
    int add = 0;

    for (int r = 0; r < NB_RESOURCES; r++) {
        add = (total[r] < max_dens->dens[r]) ? rand() % dist.refill[r] : 0;
        tile->resources[r] += add;
        total[r] += add;
    }
}

static void refill_map(tile_t **tiles,
    pos_t size,
    density_t *max_dens,
    bool biome_active)
{
    int x = 0;
    int y = 0;
    int area = size.x * size.y;
    int total[NB_RESOURCES] = {0};
    biome_distribution_t dist;
    int indices[area];

    create_shuffled_indices(indices, area);
    get_total(total, size.x, size.y, tiles);
    for (int i = 0; i < area; i++) {
        x = indices[i] / size.y;
        y = indices[i] % size.y;
        dist = get_refill_status(biome_active, x, y, tiles);
        refill_tile_resources(&tiles[x][y], dist, total, max_dens);
    }
}

static void generate_noise(tile_t **map_tiles, int Y)
{
    int tmp = 0;

    for (int x = 0; map_tiles[x] != NULL; x++) {
        for (int y = 0; y < Y; y++) {
                map_tiles[x][y].noise = perlin_2d(x, y, 0.3, 4);
        }
    }
}

void *map_thread(void *arg)
{
    serverdata_t *server = (serverdata_t *)arg;
    density_t all_dens = init_density(WORLD_DENS(server->args));

    generate_noise(server->game_data.map.tiles, server->args->height);
    pthread_mutex_lock(&(server->game_data.map.mutex));
    first_map_refill(server->args->height,
        server->game_data.map.tiles, server->args->biome);
    refill_map(server->game_data.map.tiles,
        (pos_t){server->args->width, server->args->height}, &all_dens,
        server->args->biome);
    pthread_mutex_unlock(&(server->game_data.map.mutex));
    while (server->is_running == true) {
        usleep(TICKS_REFILLS / server->args->freq);
        pthread_mutex_lock(&(server->game_data.map.mutex));
        refill_map(server->game_data.map.tiles,
            (pos_t){server->args->width, server->args->height}, &all_dens,
            server->args->biome);
        pthread_mutex_unlock(&(server->game_data.map.mutex));
    }
    return EXIT_SUCCESS;
}
