/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** look
*/

#ifndef LOOK_H_
    #define LOOK_H_

    #define NB_FOOD_BEGIN 10

    #include "pos.h"

    #define NB_TILES_LOOK 16

static const pos_t N_LOOK_TILES[] = {
    {0, 0},
    {-1, -1},
    {0, -1},
    {1, -1},
    {-2, -2},
    {-1, -2},
    {0, -2},
    {1, -2},
    {2, -2},
    {-3, -3},
    {-2, -3},
    {-1, -3},
    {0, -3},
    {1, -3},
    {2, -3},
    {3, -3}
};

static const pos_t E_LOOK_TILES[] = {
    {0, 0},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {-2, 2},
    {-2, 1},
    {-2, 0},
    {-2, -1},
    {-2, -2},
    {-3, 3},
    {-3, 2},
    {-3, 1},
    {-3, 0},
    {-3, -1},
    {-3, -2},
    {-3, -3}
};

static const pos_t S_LOOK_TILES[] = {
    {0, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {2, 2},
    {1, 2},
    {0, 2},
    {-1, 2},
    {-2, 2},
    {3, 3},
    {2, 3},
    {1, 3},
    {0, 3},
    {-1, 3},
    {-2, 3},
    {-3, 3}
};

static const pos_t W_LOOK_TILES[] = {
    {0, 0},
    {1, -1},
    {1, 0},
    {1, 1},
    {2, -2},
    {2, -1},
    {2, 0},
    {2, 1},
    {2, 2},
    {3, -3},
    {3, -2},
    {3, -1},
    {3, 0},
    {3, 1},
    {3, 2},
    {3, 3}
};

static const pos_t *LOOK_TILES[] = {
    N_LOOK_TILES,
    E_LOOK_TILES,
    S_LOOK_TILES,
    W_LOOK_TILES
};


#endif /* !GAME_H_ */
