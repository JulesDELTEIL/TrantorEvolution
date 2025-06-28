/*
** EPITECH PROJECT, 2025
** TrantorEvolution
** File description:
** init_game
*/

#include <stdlib.h>
#include <string.h>
#include "serverdata.h"
#include "fdarray.h"
#include "utils.h"
#include "map.h"

team_t *init_teams(char **teams_name, int clientnb, int nbteams)
{
    team_t *teams;

    teams = malloc(sizeof(team_t) * nbteams);
    for (int i = 0; teams_name[i] != NULL; i++) {
        teams[i].name = strdup(teams_name[i]);
        teams[i].space_left = clientnb;
        teams[i].level_max = 0;
        teams[i].eggs = NULL;
    }
    return teams;
}

int get_nb_of_teams(arguments_t *args)
{
    int nbteams = 0;

    for (; args->team_name[nbteams] != NULL; nbteams++);
    return nbteams;
}

static int init_spawn(game_t *game, uint_t w, uint_t h)
{
    uint_t x = 0;
    uint_t y = 0;

    pos_t try = {0, 0};
    x = rand() % w;
    y = rand() % h;
    try.x = x;
    try.y = y;
    game->spawn = try;
    game->map.tiles[x][y].biome = PLAINS;
    return EXIT_SUCCESS;
}

game_t init_game(arguments_t *args)
{
    game_t game_data;

    game_data.nb_of_teams = get_nb_of_teams(args);
    game_data.map.tiles = init_map(args->width, args->height);
    pthread_mutex_init(&(game_data.map.mutex), NULL);
    game_data.players = NULL;
    game_data.next_player = 0;
    game_data.next_egg = 0;
    game_data.teams = init_teams(args->team_name,
    args->clientnb, game_data.nb_of_teams);
    init_spawn(&game_data, args->width, args->height);
    return game_data;
}
