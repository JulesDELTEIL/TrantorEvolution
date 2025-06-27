/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include "map.h"
    #include "app.h"
    #include "args.h"
    #include "fdarray.h"
    #include "team.h"
    #include "pos.h"

    #define NB_FOOD_BEGIN 10

typedef struct game_s {
    map_t map;
    player_t *players;
    size_t next;
    team_t *teams;
    int nb_of_teams;
    pos_t spawn;
} game_t;

/*Functions that init the game data, the map, and every teams*/
game_t init_game(arguments_t *args);

#endif /* !GAME_H_ */
