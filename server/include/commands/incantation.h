/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** incantation.h
*/

#ifndef INCANTATION_H_
    #define INCANTATION_H_

typedef struct requirements_s requirements_t;

struct requirements_s {
    int players;
    int resources[7];
};

static const requirements_t ELEVATION_REQ[] = {
    {0, {0, 0, 0, 0, 0, 0, 0}}, // LEVEL 0 (unused)
    {1, {0, 1, 0, 0, 0, 0, 0}}, // LEVEL 1 to 2
    {2, {0, 1, 1, 1, 0, 0, 0}}, // LEVEL 2 to 3
    {2, {0, 2, 0, 1, 0, 2, 0}}, // LEVEL 3 to 4
    {4, {0, 1, 1, 2, 0, 1, 0}}, // LEVEL 4 to 5
    {4, {0, 1, 2, 1, 3, 0, 0}}, // LEVEL 5 to 6
    {6, {0, 1, 2, 3, 0, 1, 0}}, // LEVEL 6 to 7
    {6, {0, 2, 2, 2, 2, 2, 1}}, // LEVEL 7 to 8
};

#endif
