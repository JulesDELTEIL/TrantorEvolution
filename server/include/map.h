/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include <pthread.h>

    #define FOOD_DENS 0.5
    #define WOOD_DENS 0.3
    #define ROCK_DENS 0.15
    #define CLAY_DENS 0.1
    #define METAL_DENS 0.1
    #define PETROL_DENS 0.08
    #define ANTIMATTER_DENS 0.05
    #define NB_RESOURCES 7
    #define NB_BIOMES 5
    #define NOT_DEFINED -1
    #define TICKS_REFILLS 20000
    #define WORLD_DENS(args) ((args)->width * (args)->height)
    #define X_COORD(i, heigt) (i / height)
    #define Y_COORD(i, heigt) (i % height)

enum biome_e {
    SEA = 0,
    FOREST,
    MOUNTAINS,
    PLAINS,
    BEACH
};

/*
struct map_t :
 - unsigned int resources = array of every resources avaible
 - unsigned int biome = current biome
*/
typedef struct tile_s {
    unsigned int resources[NB_RESOURCES];
    unsigned int biome;
} tile_t;

typedef struct map_s {
    tile_t **tiles;
    pthread_mutex_t mutex;
} map_t;

/*
init the map depending of the width and heigt
*/
tile_t **init_map(int X, int Y);

/*
init the thread for the map
*/
void *map_thread(void *arg);

/*
struct biome_distribution_t :
 - biome_start = biome start value for every tiles
 - refill = reffils value for every tiles
*/
typedef struct biome_distribution_s {
    int biome_start[NB_RESOURCES];
    int refill[NB_RESOURCES];
} biome_distribution_t;

/*
max density for every resources
*/
typedef struct density_s {
    unsigned int dens[NB_RESOURCES];
} density_t;

const static biome_distribution_t biome_distributions[] = {
    [SEA] = {
        .biome_start = {3, 0, 0, 0, 0, 2, 0},
        .refill = {3, 1, 1, 1, 2, 1, 1}
    },
    [FOREST] = {
        .biome_start = {3, 2, 0, 0, 0, 0, 0},
        .refill = {3, 3, 1, 1, 1, 1, 1}
    },
    [MOUNTAINS] = {
        .biome_start = {3, 0, 2, 0, 0, 0, 0},
        .refill = {3, 1, 2, 1, 1, 1, 1}
    },
    [PLAINS] = {
        .biome_start = {3, 0, 0, 2, 0, 0, 0},
        .refill = {3, 1, 1, 3, 1, 1, 1}
    },
    [BEACH] = {
        .biome_start = {3, 0, 0, 2, 0, 2, 0},
        .refill = {3, 1, 1, 2, 2, 1, 1}
    }
};

#endif /* !MAP_H_ */
