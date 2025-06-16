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

enum biome_e {
    SEA = 0,
    FOREST,
    MOUNTAINS,
    PLAINS,
    BEACH
};

enum ressources_e {
    FOOD = 0,
    WOOD,
    ROCK,
    CLAY,
    METAL,
    PETROL,
    ANTIMATTER
};

typedef struct map_s {
    unsigned int resources[6];
    unsigned int biome;
} map_t;

/*init the map depending of the width and heigt*/
map_t **init_map(int X, int Y);

#endif /* !MAP_H_ */
