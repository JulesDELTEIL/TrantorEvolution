/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

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
map_t **init_map(int X, int Y)

#endif /* !MAP_H_ */
