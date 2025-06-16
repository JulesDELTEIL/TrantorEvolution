/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #define FOOD_DENS 0.5
    #define WOOD_DENS 0.3
    #define ROCK_DENS 0.15
    #define CLAY_DENS 0.1
    #define METAL_DENS 0.1
    #define PETROL_DENS 0.08
    #define ANTIMATTER_DENS 0.05
    #define NB_RESOURCES 7
    #define WORLD_DENS(args) ((args)->width * (args)->height)

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
typedef struct map_s {
    unsigned int resources[7];
    unsigned int biome;
} map_t;

/*init the map depending of the width and heigt*/
map_t **init_map(int X, int Y);

typedef struct {
    int biome_start[7];
} biome_distribution_t;

typedef struct density_s {
    unsigned int dens[7];
} density_t;

const static biome_distribution_t biome_distributions[] = {
    [SEA] = {{5, 0, 0, 0, 0, 2, 0}},
    [FOREST] = {{5, 2, 0, 0, 0, 0, 0}},
    [MOUNTAINS] = {{5, 0, 2, 0, 0, 0, 0}},
    [PLAINS] = {{5, 0, 0, 2, 0, 0, 0}},
    [BEACH] = {{5, 0, 0, 2, 0, 2, 0}}
};

#endif /* !MAP_H_ */
