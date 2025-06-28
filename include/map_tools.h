/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** mapTools
*/

#ifndef MAPTOOLS_H_
    #define MAPTOOLS_H_
    #define TICKS_REFILLS 20000
    #define NB_RESOURCES 7
    #define NB_BIOMES 5
    #define NOT_DEFINED -1

enum biome_e {
    SEA = 0,
    FOREST,
    MOUNTAINS,
    PLAINS,
    BEACH,
    EMPTY
};

/*
struct biome_distribution_t :
 - biome_start = biome start value for every tiles
 - refill = reffils value for every tiles
*/
typedef struct biome_distribution_s {
    int biome_start[NB_RESOURCES];
    int refill[NB_RESOURCES];
} biome_distribution_t;

const static biome_distribution_t biome_distributions[] = {
    [SEA] = {
        .biome_start = {0, 0, 0, 0, 0, 3, 0},
        .refill = {3, 1, 1, 1, 2, 1, 1}
    },
    [FOREST] = {
        .biome_start = {0, 3, 0, 0, 0, 0, 0},
        .refill = {3, 3, 1, 1, 1, 1, 1}
    },
    [MOUNTAINS] = {
        .biome_start = {0, 0, 3, 0, 0, 0, 0},
        .refill = {3, 1, 2, 1, 1, 1, 1}
    },
    [PLAINS] = {
        .biome_start = {0, 0, 0, 3, 0, 0, 0},
        .refill = {3, 1, 1, 3, 1, 1, 1}
    },
    [BEACH] = {
        .biome_start = {0, 0, 0, 3, 0, 2, 0},
        .refill = {3, 1, 1, 2, 2, 1, 1}
    }
};
/*
Distribution without the biome flag
*/
const static biome_distribution_t normal_distributions[] = {
    [SEA] = {
        .biome_start = {0, 0, 0, 0, 0, 0, 0},
        .refill = {3, 2, 2, 2, 2, 2, 2}
    },
    [FOREST] = {
        .biome_start = {0, 0, 0, 0, 0, 0, 0},
        .refill = {3, 2, 2, 2, 2, 2, 2}
    },
    [MOUNTAINS] = {
        .biome_start = {0, 0, 0, 0, 0, 0, 0},
        .refill = {3, 2, 2, 2, 2, 2, 2}
    },
    [PLAINS] = {
        .biome_start = {0, 0, 0, 0, 0, 0, 0},
        .refill = {3, 2, 2, 2, 2, 2, 2}
    },
    [BEACH] = {
        .biome_start = {0, 0, 0, 0, 0, 0, 0},
        .refill = {3, 2, 2, 2, 2, 2, 2}
    }
};

#endif /* !MAPTOOLS_H_ */
