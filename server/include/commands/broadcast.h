/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast.h
*/

#ifndef BROADCAST_H_
    #define BROADCAST_H_

    #define ABS(x) ((x < 0) ? -(x) : (x))

    #define REV(x, size) ((x < 0) ? (x + size) : (x - size))

    #define PI 3.14159265358979323846

    #define A_TILE_1_END 18
    #define A_TILE_2_END 72
    #define A_TILE_3_END 108
    #define A_TILE_4_END 161
    #define A_TILE_5_END 198
    #define A_TILE_6_END 251
    #define A_TILE_7_END 288
    #define A_TILE_8_END 341

static const int PLAYER_DIR_INCIDENCE[5][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 7, 8, 1, 2, 3, 4, 5, 6}, // N
    {0, 1, 2, 3, 4, 5, 6, 7, 8}, // E
    {0, 3, 4, 5, 6, 7, 8, 1, 2}, // S
    {0, 5, 6, 7, 8, 1, 2, 3, 4}  // W
};

#endif
