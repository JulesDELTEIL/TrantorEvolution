/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_
    #include "map_tools.h"
    #include <pthread.h>
    #define FOOD_DENS 0.5
    #define WOOD_DENS 0.3
    #define ROCK_DENS 0.15
    #define CLAY_DENS 0.1
    #define METAL_DENS 0.1
    #define OIL_DENS 0.08
    #define ANTIMATTER_DENS 0.05
    #define WORLD_DENS(args) ((args)->width * (args)->height)
    #define X_COORD(i, heigt) (i / height)
    #define Y_COORD(i, heigt) (i % height)

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
max density for every resources
*/
typedef struct density_s {
    unsigned int dens[NB_RESOURCES];
} density_t;

#endif /* !MAP_H_ */
