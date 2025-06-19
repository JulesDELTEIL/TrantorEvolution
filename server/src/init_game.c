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

#include <stdio.h>

static int init_spawn(game_t *game, uint_t w, uint_t h)
{
    pos_t try = {0, 0};

    // printf("w = %d h = %d\n", w, h);
    // while (game->trantor_map[try.y][try.x].biome == SEA) {
    //     printf("x = %d y = %d\n", try.x, try.y);
    //     try.x += 1;
    //     if (try.x >= w) {
    //         try.y += 1;
    //         try.x = 0;
    //     }
    //     if (try.y >= h)
    //         return EXIT_FAILURE;
    // }
    game->spawn = try;
    return EXIT_SUCCESS;
}

game_t init_game(arguments_t *args)
{
    game_t game_data;

    game_data.nb_of_teams = get_nb_of_teams(args);
    game_data.trantor_map = init_map(args->width, args->height);
    game_data.players = NULL;
    game_data.next = 0;
    game_data.teams = init_teams(args->team_name,
    args->clientnb, game_data.nb_of_teams);
    init_spawn(&game_data, args->width, args->height);
    return game_data;
}
