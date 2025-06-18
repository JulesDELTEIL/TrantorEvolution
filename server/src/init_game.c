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
    }
    return teams;
}

int get_nb_of_teams(arguments_t *args)
{
    int nbteams = 0;

    for (; args->team_name[nbteams] != NULL; nbteams++);
    return nbteams;
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
    return game_data;
}
