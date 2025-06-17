/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include "map.h"
    #include "fdarray.h"
    #include "app.h"
    #include "args.h"

typedef struct team_s {
    char *name;
    int space_left;
    int *players;
} team_t;

typedef struct game_s {
    map_t **trantor_map;
    player_t *players;
    team_t *teams;
    int nb_of_teams;
} game_t;

/*Functions that init the game data, the map, and every teams*/
game_t init_game(arguments_t *args);

#endif /* !GAME_H_ */
