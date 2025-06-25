/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** team.h
*/

#ifndef TEAM_H_
    #define TEAM_H_

    #include "pos.h"

typedef struct egg_s {
    pos_t pos;
    struct egg_s *next;
} egg_t;

typedef struct team_s {
    char *name;
    int space_left;
    egg_t *eggs;
} team_t;

#endif /* !GAME_H_ */
